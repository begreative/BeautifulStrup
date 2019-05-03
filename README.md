# beautifulStroup
C++ final project

<h2>Motivation</h2><br/>
This project was created for the user to breakdown complex project architecture into simpler forms. 
For example, given a python file directory, the user can find the defintion of a functions, see the relationships between various function. 

<h2>Design</h2>
We read 
  
<h2>Setup</h2>
<pre>
$ brew install boost<br/>
$ brew tap nlohmann/json 
$ brew install nlohmann_json</pre>

<h2>Running the tests</h2>
<pre>./test_soup FILE.py DIRECTORY</pre>



<h2>Documentation</h2><br/>
<pre> The 3 main functions are 
  <li> void find_defintion(std::string file, std::string func, std::string dir) <br/>
  This function finds the location of the method in a class and prints out the method for the user
  <li> void find_invocation(std::string file, std::string func, std::string dir) <br/>
  This function finds where the method is invoked in all other classes
  <li> void find_relationships(std::string dir) <br/>
  This function gives the user the relationships between the different functions in a class</pre>


<h2>Authors</h2>
Ben Arbib (ba2490) <br/>
Vikram Ho (vwh2107)<br/>
Gael Zendejas (gz2255)<br/>


