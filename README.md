# BeautifulStrup
## A Parser for Python Projects

</br>

### Overview
Designed for working with large Python projects, BeautifulStrup is C++ open 
source library that allows users to query certain details about the Python 
source code. 

Here's one simple example of one library function: <br>
*Given a Python file, the name of a method therein, and a Python project (a 
directory of one or more Python source files), print everywhere that function
is being called*

**find_add.cpp**
```cpp
#include <BeautifulStrup>

int main(int argc, char const *argv[]) {
  functions::find_invocation(argv[1], "add", argv[2]);
}
```
Here's what running this code would look like:
```bash
$ ./a.out foo.bar ./foo_files
>> 
bar.py: line 4, line 33
baz.py: line 78
```

Information on all the functions and data types available in the library can be
found in the documentation. 
  
</br>

### Installation

#### Requirements
* UNIX or UNIX-like operating system (e.g. MacOS, a Linux distribution, etc.)
* Python 2.7 or higher
* `pip` package manager for Python
* `brew` or comparable package management system

#### Dependencies
```bash
$ pip install astexport
$ brew install boost
$ brew tap nlohmann/json 
$ brew install nlohmann_json
```

#### Usage
When you download or clone this repo, for now, you'll need to have the directory
in the same file where you plan on using it. Then you need only add 
`#include "BeautfiulStrup.h"` to your `.cpp` file. We're currently working on an
installation script that will install all these dependencies, as well as add a
linked library file to your `usr/local/include` path for easier use.

</br>


### Documentation
Found in BeautifulStrup.pdf (will be creating github webpage soon)

</br>

### Supported Compilers
Currently, the following compilers are known to work: GCC 4.8 - 9.0 (and possibly later)
This ran on C++17. 

</br>

### Authors
Ben Arbib (ba2490)
Vikram Ho (vwh2107)
Gael Zendejas (gz2255)