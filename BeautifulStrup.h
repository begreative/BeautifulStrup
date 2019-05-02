#include <string>

#ifndef BEAUTIFULSTRUP_H_
#define BEAUTIFULSTRUP_H_

namespace functions {

    void find_invocations(std::string file, std::string func, std::string dir);
    void find_defintion(std::string file, std::string func, std::string dir);

}


namespace classes {

    void find_relationships(std::string dir);

}


#endif /* BEAUTIFULSTRUP_H_ */