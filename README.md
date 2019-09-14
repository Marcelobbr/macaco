# macaco
In this project we have built a C++ library that provides an interface similar to Pandas package in Python.
A DataFrame can have one index column and many data columns of any built-in or user-defined type.

**macaco** should be used inside Python. Because it is  optimized in C++, it should provide much faster data
structures which are allowed in pure Python. 

## Main Features
Here is a list of allowed operations:
* insert(array_values,column_name): inserts a new column
* remove(column_name): deletes a specific column
* tolist(column_name): shows list of values from a specific column
* locateCel(column_name): shows value from a specific cell
* locateRow(column_name): shows list of values from a specific row
* toIndxCol(self, column): indexes column values using optimization algorithm from Binary-Search Tree
* show(): shows all table data in a way very similar to pandas dataframe
* plot(columnA, columnB):  plots a 2d graphic using data from 2 columns

## Team members
* Lucas
* [Marcelo B. Barata Ribeiro](https://www.linkedin.com/in/marcelo-barata-ribeiro-213b8733/)

## Background
This is a final project related to the class Estrutura de Dados e Algoritmos at [EMAp-FGV](https://emap.fgv.br), ministered by professor Jorge Poco.

## Files List
* macaco.py: main module which imports c++ functionalities and translate them to python syntax. 
* test_from_macaco.ipynb: jupyter notebook file which imports macaco.py and does tests with all macaco methods to verify its functionalities
* test_from_note.ipynb: similar to the version above, but the methods are built inside the notebook. It is a better alternative than above to prototype new methods.
* dfbuilder.cpp: main C++ file whose functionalities macaco.py imports
* treeIndexing.cpp: BST algorithm to optimize indexation whose methods are imported and used by dfbuilder.cpp
* gen_shared_lib.sh: a compiler which compiles c++ code to shared library. It compiles dfbuilder.cpp
* dfbuilder.so: the resulting shared library from the gen_shared_lib.sh compilation

## How to run it
In spite of all the dependencies of C++, the .so file is already built for you. In case of malfunctioning, we strongly recommend that you fully read the Requirements section below.

There is a python test file for you to test the program. It's name is test.ipynb. It's easier to do your own tests using jupyter notebook, but if you prefer to use pure python, just run the corresponding .py file. 
To run the python file, run on terminal
```sh
python3 hello.py
```
Or simply activate the jupyter notebook.

There, all configuration of macaco is imported as mc.

## Requirements
If you are used to Linux and Python, this section isn't necessary, except in case of any malfunctioning or low experience with those softwares.

### Operating System
All the system was built using Linux Ubuntu. We strongly recommend that you also use a Linux Distribution or at least an OS from Unix family. In case you are using Windows, we suggest you to operate inside a Virtual Machine. Just follow one of the guides below:
* [lifewire guide](https://www.lifewire.com/run-ubuntu-within-windows-virtualbox-2202098)
* [VirtualBox guide](https://www.virtualbox.org/manual/ch01.html)

You will need the Ubuntu installer ISO file, which can be found at Ubuntu website. We worked with Ubuntu 18.04.3 LTS. LTS stands for long-term support and we suggest you to also choose LTS versions.
* [Ubuntu installer](https://ubuntu.com/download/desktop)

In Ubuntu, you will see that both C++ and Python are already installed, which is a great shortcut for you. Nevertheless, there are also some considerations about these programming languages. See below.

### C++

<!-- For C++ programming language, here are packages which are necessary for the program to run correctly:
* cppimport==18.11.8
* Mako==1.1.0
* MarkupSafe==1.1.1
* pybind11==2.3.0 -->

To compile c++ on ubuntu, go to terminal by pressing Ctr+Shift+T and type:
```sh
g++ -std=c++17 <filename>.cpp
./a.out
```
<-std=c++17> is optional. It defines the version of c++ to c++17. Otherwise is uses c++11 as standard.

There are two Linux C/C++ library types that can be created. Those are Static libraries (.a) and Dynamically linked shard object libraries (.so). Here we worked with shared libraries.

To generate a shared library:
```sh
g++ -std=c++17 -I /usr/include/python3.6 -fpic -c -o <your_cpp_file>.o <your_cpp_file>.cpp
g++ -o <your_cpp_file>.so -shared <your_cpp_file>.o -lboost_python3
```

But to make life easier for you, we have already built an .sh file which you just need to compile so that you generate a .so file which will be imported by python. To run this .sh file, type on terminal on the corresponding folder:
```sh
bash <name_of_sh_file>.sh
```
Our naming conventions for the cpp file and the .sh file (but you should confirm it yourself):
* `dfbuild.cpp`
* `gen_shared_lib.sh`

If you need more details about shared libraries, check [this link](https://helloacm.com/calling-c-shared-library-from-python-code-linux-version/)

#### pyboost package
pyboost package was essential for this project and its instalation is also a requirement.
To install it, go to terminal and type:
```sh
sudo apt-get install libboost-all-dev
```
Learning how to use pyboost isn't necessary, because all the scripts which use it are already built, but if you want to learn how it works, just follow [this link](https://www.boost.org/doc/libs/1_68_0/libs/python/doc/html/tutorial/index.html#tutorial.quickstart) which has documentation and tutorial.


### Python
We chose Python3 version of Python, while the standard version from Ubuntu is Python2. As there are some differences between the two versions, we suggest that you install python3. Anaconda is pretty handy to work with python, but it is not vital in this case, as we are not using any external Python package.

## Looking Forward
Here are some improvements which could be made:
* Code refactoring: columns accept strings, ints and floats, but there should be a less verbose way to do it instead of our c++ code.
* Optimized indexation: The indexation was done by using Binary-Search tree algorithm, but there are other algorithms which guarantee a more balanced tree, reducing runtime, such as Red-black trees and B-trees. 
* Handling of missing data (represented as NaN) in floating point as well as non-floating point data
* Powerful, flexible group by functionality to perform split-apply-combine operations on data sets, for both aggregating and transforming data
* Make it easy to convert differently-indexed data in other Python and NumPy data structures into DataFrame objects
* Intuitive merging and joining data sets
* Flexible reshaping and pivoting of data sets
* Robust IO tools for loading data from flat files (CSV and delimited), Excel files and SQL databases
* Time series functionalities: handling of datetime, timeframe, date shifting and lagging, etc.
* geolocated data: some solution to work on geolocated data, preferably by using k-d trees, which are a better optimization solution.