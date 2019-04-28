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

int assign_if_main(json p_main){
  int got_main = 0;
  int got_name = 0;
  if (p_main.count("test")){
    json test = p_main["test"];
    string left_id;
    string comparators;
    
    if(test.count("comparators")){
        json comp = test["comparators"][0];
        if (comp.count("func") && comp["func"].count("s"))
            comparators = comp["func"]["s"].get<string>();;
    }
    if(test.count("left") && test["left"].count("id")){
        left_id = test["left"]["id"].get<string>();
    }
    
    if (!left_id.compare("__name__") || !comparators.compare("__name__"))
      got_name = 1;

    if (!left_id.compare("__main__") || !comparators.compare("__main__"))
      got_main = 1;
  }
  
  return (got_main && got_name);
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
    if (argc < 2){
        cout << "enter .json file/s" << endl;
        exit(0);
    }
    vector <struct classDef> classes;
    int found_main;
    std::ifstream i(argv[1]);
    json j;
    i >> j;

    json body= j["body"];
    // iterate the array
    for (json::iterator it = body.begin(); it != body.end(); ++it) {
      json entry = it.value();
//    cout << entry["ast_type"] << endl;
      if (entry.count("ast_type") && 
          !entry["ast_type"].get<std::string>().compare("ClassDef"))
        classes.push_back(create_class_def(entry));
//    cout << "============" << endl;
      if (entry.count("ast_type") && 
          !entry["ast_type"].get<string>().compare("If"))
        found_main = assign_if_main(entry);
    }
    if (found_main)
      cout << "Found main" << endl;
    print_classes(classes);

    return 0;
}


