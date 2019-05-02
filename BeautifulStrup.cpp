#include <iostream>
#include <cstdlib>
#include <fstream>

#include "BeautifulStrup.h"
#include <nlohmann/json.hpp>

namespace functions {

    void find_invocations(std::string file, std::string fname, std::string dir) {

        system("chmod u+x py_to_json.sh");
        std::string tmp = "./py_to_json.sh " + file;
        const char *command = tmp.c_str();
        system(command);

        std::string pyext = ".py";
        std::string jext = "AST.json";

        std::string::size_type n = file.rfind("/") + 1;
        std::string jfile = file.substr(n);
        jfile.replace(jfile.find(pyext), pyext.length(), jext);
        
        std::ifstream i(jfile);
        nlohmann::json j;
        i >> j;
        
        nlohmann::json body = j["body"];
        for(nlohmann::json::iterator it = body.begin(); it != body.end(); it++) {
            nlohmann::json entry = it.value();
            if(entry.count("ast_type") && entry["ast_type"].get<std::string>().compare("Class"))
                std::cout << entry["ast_type"] << std::endl;
        }


    }

}


namespace classes {

}


namespace files {


}