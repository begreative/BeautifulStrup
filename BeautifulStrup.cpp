#include <iostream>
#include <cstdlib>
#include <fstream>

#include <vector>
#include <boost/filesystem.hpp>


#include "BeautifulStrup.h"
#include <nlohmann/json.hpp>

/* HELPER FUNCTIONS DECLARATIONS:
 * Intentionally excluded from header file so as to be used exclusively here
 */

std::string create_json(std::string file); //Given a python file, creates AST in JSON format
nlohmann::json open_json(std::string file); //Given a JSON file, opens and returns a JSON object
classes::file create_file_class(nlohmann::json j);
std::vector<nlohmann::json> dir_to_json_files(std::string dir);
std::string get_import(nlohmann::json entry);
methods::method get_method(nlohmann::json entry);
classes::cls get_class(nlohmann::json entry);
void print_method(methods::method m ,std::string file_name);
methods::method find_method(classes::file f, std::string name);
methods::method find_method_from_vector(std::vector<methods::method> methods, std::string name);
int get_last_line(nlohmann::json entry, int curr);

namespace methods {

    method::method(){
        name = "";
    }
    method::~method(){
        // do nothing
    }
    //TODO: find everywhere its being used
/* LIBRARY FUNCTIONS:
 * Declared in header file as to be used externally
 */

    //TO DO: GAEL
    void find_invocations(std::string file, std::string func, std::string dir) {
        // std::vector<nlohmann::json> json_vec = dir_to_json_files(dir);
        nlohmann::json j = open_json(create_json(file));

        nlohmann::json body = j["body"];
        for(nlohmann::json::iterator it = body.begin(); it != body.end(); it++) {
            nlohmann::json entry = it.value();
            /* code to capture/save function from source file */
        }
        // found func name and var amnt
    }

    //TODO: find where the function lives
    void find_defintion(std::string file, std::string func, std::string dir) {
        // std::vector<nlohmann::json> json_vec = dir_to_json_files(dir);
        namespace fs = boost::filesystem;
        std::vector<classes::file> files;
        nlohmann::json j = open_json(create_json(file));

        for (fs::recursive_directory_iterator end, d(dir); d != end; ++d ) {
            if(fs::is_directory(d->path()))
                continue;
            if(d->path().string().find(".py") != std::string::npos) {
                std::string py_name = d->path().string();
                std::string jn = create_json(py_name);
                nlohmann::json j = open_json(jn);
                classes::file f = (create_file_class(j));
                f.name = py_name;
                files.push_back(f);
                /* code to identify function calls in given python file */
            }

            for(classes::file f : files){
                methods::method m = find_method(f, func);
                if(m.name.compare("1")){
                    print_method(m, f.name);
                }
            }
        }

        // for (std::vector<nlohmann::json>::iterator it = json_vec.begin() ; 
        //                                     it != json_vec.end(); ++it){
        //     files.push_back(create_file_class(*it));
        //                                     }
        // look for standalone methods
        // look inside classes
    }
}

namespace classes {
    cls::cls(){
        name = "";
    };

    cls::~cls(){
        //not much to do;
    };

    file::file()
    {
        name = "";
    };

    file::~file(){
        //not much to do;
    };

    //TOD DO:
    void find_relationships(std::string dir){
    }

}

/* HELPER FUNCTIONS:
 * Functions below intentionally excluded from header file so as to be private
 */

classes::file create_file_class(nlohmann::json j){
        classes::file f;
        // f.name = file_name;

        for (nlohmann::json::iterator it = j.begin(); it != j.end(); it++){
            nlohmann::json entry = it.value();
            if (entry.count("ast_type")){
                std::string ast_type = entry["ast_type"].get<std::string>();
                if (!ast_type.compare("Import"))
                    f.import.push_back(get_import(entry));
                else if (!ast_type.compare("If"))
                    continue;
                else if (!ast_type.compare("ClassDef"))
                    f.classes.push_back(get_class(entry));
            }
        }
    return f;
    }

std::string create_json(std::string file) {

    system("chmod u+x py_to_json.sh");
    std::string tmp = "./py_to_json.sh " + file;
    const char *command = tmp.c_str();
    system(command);

    std::string pyext = ".py";
    std::string jext = "AST.json";

    std::string::size_type n = file.rfind("/") + 1;
    std::string jfile = file.substr(n);
    jfile.replace(jfile.find(pyext), pyext.length(), jext);

    return jfile;
}


nlohmann::json open_json(std::string jfile) {
    std::ifstream i(jfile);
    nlohmann::json j;
    i >> j;

    return j;
}

std::vector<nlohmann::json> dir_to_json_files(std::string dir){
    namespace fs = boost::filesystem;
    std::vector<nlohmann::json> json_vector;

    for (fs::recursive_directory_iterator end, d(dir); d != end; ++d ) {
        if(fs::is_directory(d->path()))
            continue;
        if(d->path().string().find(".py") != std::string::npos) {
            std::string jn = create_json(d->path().string());
            json_vector.push_back(open_json(jn));
            /* code to identify function calls in given python file */
        }
    }
    return json_vector;
}

std::string get_import(nlohmann::json entry){
    return entry["names"]["name"];
}

methods::method get_method(nlohmann::json entry){
    methods::method mthd;
    nlohmann::json body = entry["body"];
    mthd.name = entry["name"];
    mthd.first_line = std::atoi(entry["lineno"].get<std::string>().c_str());
    mthd.last_line = get_last_line(entry, mthd.first_line);

    // add all args
    if(entry.count("args") && entry["args"].count("args")){
        nlohmann::json args = entry["args"]["args"];
        for (nlohmann::json::iterator it = args.begin(); it != args.end(); it++){
            nlohmann::json entry = it.value();
            mthd.args.push_back(entry["arg"]);
        }
    }
    return mthd;
}

classes::cls get_class(nlohmann::json j){
    classes::cls new_cls;
    nlohmann::json body = j["body"];
    new_cls.name = j["name"].get<std::string>();
    for (nlohmann::json::iterator it = body.begin(); it != body.end(); it++){
        nlohmann::json entry = it.value();
        if (entry.count("ast_type")){
            std::string ast_type = entry["ast_type"].get<std::string>();
            if (!ast_type.compare("FunctionDef"))
                new_cls.methods.push_back(get_method(entry));
        }
    }
    return new_cls;
}

void print_method(methods::method m, std::string file_name){
    
    return;
}

methods::method find_method(classes::file f, std::string name){
    methods::method m;

    for(classes::cls c: f.classes){
        m = find_method_from_vector(c.methods, name);
        if (m.name.compare("1"))
            return m;
    }

    m = find_method_from_vector(f.methods, name);
    if (m.name.compare("1"))
        return m;

    return m;
}

methods::method find_method_from_vector(std::vector<methods::method> methods, std::string name){
    methods::method dummy;
    dummy.name = "1";
    for(methods::method m : methods){
        if (!m.name.compare(name))
            return m;
    }
    return dummy;
}

int get_last_line(nlohmann::json body, int curr){

    for (nlohmann::json::iterator it = body.begin(); it != body.end(); it++){
    nlohmann::json entry = it.value();
    if(entry.count("lineno")){
        int line = std::atoi(entry["lineno"].get<std::string>().c_str());
        curr = curr >= line? curr: line;
        }
    int next_block = get_last_line(entry, curr);
    curr = curr >= next_block? curr : next_block;
    }
    return curr;
}