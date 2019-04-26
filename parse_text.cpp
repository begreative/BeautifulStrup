#include <iostream>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#define MAX_LINE 256

using namespace std;
using json = nlohmann::json;

struct method{
  string name;
  vector<string> args;
};

struct classDef{
    vector<struct method> methods;
    string name;
};

vector <string>get_args(json args){
  vector <string> arg_names;
  for(json::iterator it = args.begin(); it != args.end(); ++it){
      json val = it.value();
      if(val.count("ast_type") && 
          val["ast_type"].get<std::string>().compare("arg") == 0)
        arg_names.push_back(val["arg"].get<std::string>());
  }
  return arg_names;
}

struct method create_method(json args, string name){
    struct method new_method;
    new_method.name = name;
    new_method.args = get_args(args["args"]);
    return new_method;
}

struct classDef create_class_def(json class_def){
  json body = class_def["body"];
  string name = class_def["name"].get<std::string>();
  struct classDef new_class;
  new_class.name = name;
  
  for(json::iterator it = body.begin(); it != body.end(); ++it){
      json val = it.value();
      if(val.count("ast_type") && 
          !val["ast_type"].get<std::string>().compare("FunctionDef")){
          new_class.methods.push_back(
              create_method(val["args"], val["name"].get<string>()));
      }
  }
  return new_class;
}

void print_variables(struct method method){
    cout << "        variables:" << endl;
    for (string var : method.args)
      cout << "        \\_ " << var << endl;
}

void print_methods(struct classDef cls){
    for (struct method m:cls.methods){
        cout << "    \\_ " << m.name << endl;
        print_variables(m);
    }
}

void print_classes(vector<struct classDef> classes){
    for (struct classDef c : classes){
      cout << "Class name: " << c.name << endl;
      print_methods(c);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2){
        cout << "enter .json file/s" << endl;
        exit(0);
    }
    vector <struct classDef> classes; 
    std::ifstream i("classes/test.json");
    json j;
    i >> j;
    json body = j["body"];

    // iterate the array
    for (json::iterator it = body.begin(); it != body.end(); ++it) {
      json entry = it.value();
      if (entry.find("ast_type") != entry.end()) {
//        cout << entry["ast_type"] << endl;
        if (!entry["ast_type"].get<std::string>().compare("ClassDef"))
          classes.push_back(create_class_def(entry));
//        cout << "============" << endl;
      }
    }
    print_classes(classes);

    return 0;
}


