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
void print_method(methods::method m ,std::string file_name, int from, int to);
methods::method find_method(classes::file f, std::string name);
methods::method find_method_from_vector(std::vector<methods::method> methods, std::string name);
int get_last_line(nlohmann::json entry, int curr);
void print_file(classes::file f);
void print_class(classes::cls c);
void print_methods(methods::method m);
void add_call_line_num(std::vector<methods::method> m, nlohmann::json entry);
void add_if_expr_to_call(std::vector<methods::method> m, nlohmann::json entry);
void add_if_assign_to_call(std::vector<methods::method> m, nlohmann::json entry);
void add_count(methods::method m, int line);
void print_methods_from_methods(methods::method m, std::string func, std::string filename);
void print_methods_from_classes(classes::cls c, std::string func, std::string filename);
void print_methods_from_file(classes::file f, std::string func);

namespace methods {

    method::method(){
        name = "";
    }
    method::~method(){
        // do nothing
    }
    
    void find_invocations(std::string file, std::string func, std::string dir) {
        namespace fs = boost::filesystem;
        std::vector<classes::file> files;

        for (fs::recursive_directory_iterator end, d(dir); d != end; ++d ) {
            if(fs::is_directory(d->path()))
                continue;
            if(d->path().string().find(".py") != std::string::npos) {
                std::string py_name = d->path().string();
                std::string jn = create_json(py_name);
                nlohmann::json jf = open_json(jn);
                classes::file f = (create_file_class(jf));
                f.name = py_name;
                files.push_back(f);
            }
        }

        for(classes::file f : files)
          print_methods_from_file(f, func);
        
    }

    //TODO: find where the function lives
    void find_defintion(std::string file, std::string func, std::string dir) {
        namespace fs = boost::filesystem;
        std::vector<classes::file> files;
        nlohmann::json j = open_json(create_json(file));

        for (fs::recursive_directory_iterator end, d(dir); d != end; ++d ) {
            if(fs::is_directory(d->path()))
                continue;
            if(d->path().string().find(".py") != std::string::npos) {
                std::string py_name = d->path().string();
                std::string jn = create_json(py_name);
                nlohmann::json jf = open_json(jn);
                classes::file f = (create_file_class(jf));
                f.name = py_name;
                files.push_back(f);
            }
        }

            for(classes::file f : files){
                methods::method m = find_method(f, func);
                if(m.name.compare("1")){ 
                    std::cout << "File: " << f.name << std::endl;
                    print_method(m, f.name, m.first_line-1, m.last_line);
                    std::cout << "" << std::endl;
                }
            }
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
        nlohmann::json body;
        // f.name = file_name;
        if (j.count("body"))
            body = j["body"];
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
                else if (!ast_type.compare("FunctionDef"))
                    f.methods.push_back(get_method(entry));
                else if(!ast_type.compare("Assign"))
                    add_if_assign_to_call(f.methods, entry);
                else if(!ast_type.compare("Expr"))
                    add_if_expr_to_call(f.methods, entry);
                else if(!ast_type.compare("Call"))
                    add_call_line_num(f.methods, entry);
            }
        }
    return f;
    }

void add_count(methods::method m, int line){
  m.called_at_line.push_back(line);
}

void print_methods_from_methods(methods::method m, std::string func, std::string filename){
  if (!m.name.compare(func)){
    std::cout << "Method \"" << func << "\" is used in file " << filename << " in lines: ";
    for (int i : m.called_at_line)
      std::cout << i << ", ";
    std::cout << "\n" << std::endl;
  }

}

void print_methods_from_classes(classes::cls c, std::string func, std::string filename){
  for(methods::method m : c.methods)
  print_methods_from_methods(m, func, filename);
}

void print_methods_from_file(classes::file f, std::string func){
  for(classes::cls c: f.classes)
    print_methods_from_classes(c, func, f.name);

  for(methods::method m : f.methods)
    print_methods_from_methods(m, func, f.name);
}

void add_call_line_num(std::vector<methods::method> m, nlohmann::json entry){
  std::string method_name;
  int line = entry["lineno"];

  if (entry.count("func") && entry["func"].count("attr"))
    method_name = entry["func"]["attr"].get<std::string>();
  else if(entry.count("func") && entry["func"].count("id"))
    method_name = entry["func"]["id"].get<std::string>();
  
  for(methods::method curr : m){
    if (!curr.name.compare(method_name)){
      add_count(curr, line);
      break;
    }
  }
}

void add_if_expr_to_call(std::vector<methods::method> m, nlohmann::json entry){
    nlohmann::json value = entry["value"];
    
    if(value.count("args")){
      nlohmann::json args = value["args"];
      for (nlohmann::json::iterator it = args.begin(); it != args.end(); it++){
        nlohmann::json curr = it.value();
        if (curr["ast_type"].get<std::string>().compare("Call"))
          add_call_line_num(m, curr);
    }
    
    if(!value["ast_type"].get<std::string>().compare("Call"))
        add_call_line_num(m, value);
  }
}

void add_if_assign_to_call(std::vector<methods::method> m, nlohmann::json entry){
  
  nlohmann::json value = entry["value"];
  if (!value["ast_type"].get<std::string>().compare("Call"))
    add_call_line_num(m, value);
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
    if (entry.count("names") && entry["names"].count("name"))
        return entry["names"]["name"];
    return "";
}

methods::method get_method(nlohmann::json entry){
    methods::method mthd;
    nlohmann::json body = entry["body"];
    mthd.name = entry["name"];

    mthd.first_line = entry["lineno"];
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

void print_method(methods::method m, std::string file_name, int from, int to){
    std::fstream f(file_name);
    std::string line;
    std::cout << "code from lines: " << from << " - " << to << std::endl;
    for (int i = 0; i <= to; i++){
        getline(f,line);
        if (i>=from)
            std::cout << line << std::endl;
    }
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
    if (body.size() <= 1)
        return 0;
    
    for (nlohmann::json::iterator it = body.begin(); it != body.end(); it++){
    nlohmann::json entry = it.value();
    if(entry.count("lineno")){
        int line = entry["lineno"];
        curr = curr > line? curr: line;
        }
    int next_block = get_last_line(entry, curr);
    curr = curr > next_block? curr : next_block;
    }

    return curr;
}

void print_methods(methods::method m){
    std::cout << "    \\_ : " << m.name << std::endl;
}

void print_class(classes::cls c){
    std::cout << "\\_ Class: " << c.name << std::endl;
    for(methods::method m: c.methods)
        print_methods(m);
}

void print_file(classes::file f){
    std::cout << "File: " << f.name << std::endl;
    for(classes::cls c: f.classes)
        print_class(c);
    for(methods::method m: f.methods)
        print_methods(m);
}
