# beautiful_c
C++ final project


# Project Proposal
## HTML Parsing Library for C++
### Introduction
In the absence of an API, when an API is too restrictive, or when an API is simply unavailable in a language needed for integration, many developers turns to tools like BeautifulSoup to parse content from a web service. BeautifulSoup provides functions that facilitate the extraction of data from web files (HTML, JavaScript, XML, CSS, etc.) through the use of the these files’ standard use of tags. While BeautifulSoup is only available for Python, a couple of options exist for C++: dlib parsing and c-plus-plus-dom. These options, however, lack two key components: one, an interface that’s as easy to use as BeautifulSoup and, two, a modern and efficient use of the latest C++ standard libraries.

### Objectives
Our goal is to create as simple and modern of an HTML parser for C++. By focusing, at least initially, on just HTML, we hope to be able to create as compact and efficient a library as possible. Because BeautifulSoup already exists, we have a good launching point (although we are hopeful to even find opportunities for improvement even within BeautifulSoup). We envision our initial steps as below:
List out all the aspects of HTML-only parsing from BeautifulSoup
Find and interview people who use BeautifulSoup, as well as one of the C++ versions 
Sketch the design for the library, starting by how it should be used based on feedback
After step three we will need to assess our timeframe and feasibility and either bring back our design to those we interviewed, proceed with implementation, or make any necessary changes to our project.

### Roles
While all three members of the project will share in the varying tasks of the project, below are the duties each will lead.

Designer (interviews, feedback loops, sketch): Vikram Ho
Engineer (architecture, efficiency, algorithms): Ben Arbib
Presenter (scheduling, write-ups, presentation): Gael Zendejas

### Testing and Measurement
The baseline test is to successfully parse basic HTML file via standard tags. The metric is that it works exactly (or better) than the key BeautifulSoup functions we choose to emulate. We will need to further develop a testing strategy after we conduct interviews with prospective users. 

### Possible Releases 
Minimum Requirements: 
Given an HTML file, functions that extract and search through standard data such as heading, body text, images, links, etc.
Use of modern C++ standard library to create usable interface (as defined by interviews)

### Want-To-Have: 
Create efficiencies either through the use of modern C++ standard library components or through better use of algorithms (or both)
Add additional BeautifulSoup functionality (e.g. parsing other types of files, supporting more HTML protocols / methods, etc.)

### The Dream:
An end-to-end web-scraping tool that both establishes connections with web servers and then downloads and parses the web content
This could create further efficiencies since we would have control over how the HTML is generated
Additionally would be a nice use experience since would delete the need to use something like wget or another library (like Selenium in Python)
Generate a library of all the tags and leverage some natural language processing techniques to more intelligently and efficiently parse the webpage and return desired results to the user
Extend the above functionality beyond tags and into common search terms for web pages such that all possibly relevant (but not explicitly stated) search terms are returned.
