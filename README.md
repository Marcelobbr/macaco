# macaco
This is a final project related to the class Estrutura de Dadose Algoritmos at [EMAp-FGV](https://emap.fgv.br), ministered by professor Jorge Poco.

In this project we have built a C++ library that provides an interface similar to Pandas package in Python.
A DataFrame can have one index column and many data columns of any built-in or user-defined type.

## Main Features
Here is a list of allowed operations:
* insertion
* deletion
* find



## Team members
* [Lucas]()
* [Marcelo B. Barata Ribeiro](https://www.linkedin.com/in/marcelo-barata-ribeiro-213b8733/)

# Background

# Files List
* 
* 
* 

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
### Operating System
All the system was built using Linux Ubuntu. We strongly recommend that you also use a Linux Distribution or at least an OS from Unix family. In case you are using Windows, we suggest you to operate inside a Virtual Machine. Just follow one of the guides below:
* [lifewire guide](https://www.lifewire.com/run-ubuntu-within-windows-virtualbox-2202098)
* [VirtualBox guide](https://www.virtualbox.org/manual/ch01.html)

You will need the Ubuntu installer ISO file, which can be found at Ubuntu website. We worked with Ubuntu 18.04.3 LTS. LTS stands for long-term support and we suggest you to also choose LTS versions.
* [Ubuntu installer](https://ubuntu.com/download/desktop)

In Ubuntu, you will see that both C++ and Python are already installed, which is a great shortcut for you. Nevertheless, there are also some considerations about these programming languages. See below.

### C++

For C++ programming language, here are packages which are necessary for the program to run correctly:
* cppimport==18.11.8
* Mako==1.1.0
* MarkupSafe==1.1.1
* pybind11==2.3.0

To compile c++ on ubuntu, go to terminal by pressing Ctr+Shift+T and type:
    g++ -std=c++17 <filename>.cpp
    ./a.out
	<-std=c++17> is optional, it defines the version of c++ to c++17. Otherwise is uses c++11as standard.

There are two Linux C/C++ library types that can be created. Those are Static libraries (.a) and Dynamically linked shard object libraries (.so). Here we worked with shared libraries.

To generate a shared library:
```sh
g++ -shared -o <foo>.so -fPIC <your_cpp_file>.cpp
g++ -Wall -fPIC -shared <your_cpp_file>.cpp -o <foo>.so
```
But to make life easier for you, we have build an .sh file which you just need to compile so that you generate an .so file which will be imported by python. To run this .sh file, type on terminal on the corresponding folder:
```sh
bash <name_of_sh_file>.sh
```
We named this .sh file as compile_pyboost, but you should confirm it yourself.

If you need more details about shared libraries, check [this link](https://helloacm.com/calling-c-shared-library-from-python-code-linux-version/)


#### pyboost package
pyboost package was essential for this project and its instalation is also a requirement.
To install it, go to terminal and type:
```sh
sudo apt-get install libboost-all-dev
```
Learning how to use pyboost isn't necessary, because all the scripts which use it are already built, but if you want to learn how it works, just follow [this link](https://www.boost.org/doc/libs/1_68_0/libs/python/doc/html/tutorial/index.html#tutorial.quickstart) which has documentation and tutorial.

	
    
    tutorial
        

### Python
We chose Python3 version of Python, while the standard version from Ubuntu is Python2. As there are some differences between the two versions, we suggest that you install python3. Anaconda is pretty handy to work with python, but it is not vital in this case, as we are not using any external Python package.

## Looking Forward
The indexations of data was done with Binary-Search Tree Algorithm
red-black trees
kd tree - para coordenadas
geolocated data
datetime
