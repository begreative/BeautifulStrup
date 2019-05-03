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

namespace methods {

    //TODO: find everywhere its being used
    void find_invocations(std::string file, std::string meth, std::string dir) {
        std::vector<classes::file> files;

/* LIBRARY FUNCTIONS:
 * Declared in header file as to be used externally
 */ 

    //TO DO: GAEL
    void find_invocations(std::string file, std::string func, std::string dir) {

        std::string jfile = create_json(file);
        nlohmann::json j = open_json(jfile);

        nlohmann::json body = j["body"];
        for(nlohmann::json::iterator it = body.begin(); it != body.end(); it++) {
            nlohmann::json entry = it.value();
            /* code to capture/save function from source file */
        }

        namespace fs = boost::filesystem;
        
        for (fs::recursive_directory_iterator end, d(dir); d != end; ++d ) {
            if(fs::is_directory(d->path()))
                continue;
            if(d->path().string().find(".py") != std::string::npos) {
                std::string jn = create_json(d->path().string());
                nlohmann::json jobj = open_json(jn);
                /* code to identify function calls in given python file */
            }
        }
        // found func name and var amnt
    }

    //TODO: find where the function lives
    void find_defintion(std::string file, std::string func, std::string dir) {
        create_json(file);
        create_json(dir);
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

    std::string get_import(nlohmann::json entry){
        return entry["names"]["name"];
    }
  
    methods::method get_method(nlohmann::json entry){
        methods::method mthd = new method();
        nlohmann::json body = entry["body"];
        mthd.name = entry["name"];

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

    classes::cls get_class(nlohmann::json entry){
        classes::cls new_cls = new cls();
        nlohmann::json body = entry["body"];
        new_cls.name = entry["name"].get<std::string>();
        for (nlohmann::json::iterator it = body.begin(); it != body.end(); it++){
            nlohmann::json entry = it.value();
            if (entry.count("ast_type")){
                std::string ast_type = entry["ast_type"].get<std::string>();
                if (!ast_type.compare("FunctionDef"))
                    new_cls.methods.push_bash(get_method(entry));
            }
        }

        return new_cls;
    }

    classes::file create_file_class(std::string file_name){
        nlohmann::json body = open_json(file_name)["body"];
        classes::file f;
        f.name = file_name;

        for (nlohmann::json::iterator it = body.begin(); it != body.end(); it++){
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
}

/* HELPER FUNCTIONS:
 * Functions below intentionally excluded from header file so as to be private
 */

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