#include <iostream>
#include <cstdlib>
#include <fstream>

#include "BeautifulStrup.h"
#include <nlohmann/json.hpp>

/* HELPER FUNCTIONS DECLARATIONS:
 * Intentionally excluded from header file so as to be used exclusively here
 */

std::string create_json(std::string file); //Given a python file, creates AST in JSON format
nlohmann::json open_json(std::string file); //Given a JSON file, opens and returns a JSON object



/* LIBRARY FUNCTIONS:
 * Declared in header file as to be used externally
 */ 

namespace functions {

    //TO DO: GAEL
    void find_invocations(std::string file, std::string func, std::string dir) {

        std::string jfile = create_json(file);
        nlohmann::json j = open_json(jfile);
        
        nlohmann::json body = j["body"];
        for(nlohmann::json::iterator it = body.begin(); it != body.end(); it++) {
            nlohmann::json entry = it.value();
            /* code to capture/save function from source file */
        }

    }


    //TO DO:
    void find_defintion(std::string file, std::string func, std::string dir) {


    }



}



namespace classes {


    //TOD DO:
    void find_relationships(std::string dir) {


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