#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#ifndef BEAUTIFULSTRUP_H_
#define BEAUTIFULSTRUP_H_

namespace methods {

    void find_invocations(std::string file, std::string meth, std::string dir);
    void find_defintion(std::string file, std::string meth, std::string dir);

    class method{
    public:
        std::string name; 
        std::vector<std::string> args;
        std::vector<int> called_at_line;
        int var_amnt;
        int first_line;
        int last_line;
        std::string obj_ref;
        std::string from_class;

        method();
        ~method();
    };
}


namespace classes {
    class cls{
    public:
        std::string name;
        std::vector<methods::method> methods;

        cls();
        ~cls();
    };

    class import{
    public:
        std::string class_name;
        std::string import_name;

        import();
        ~import();
    };

    class file{
    public:
        std::string name;
        std::vector<cls> classes;
        std::vector<methods::method> methods;
        std::vector<classes::import> imports;

        file();
        ~file();
    };

    // void create_file_trees(std::string dir);
    file create_file_class(std::string file_name);
    void find_relationships(std::string dir);

}


#endif /* BEAUTIFULSTRUP_H_ */
