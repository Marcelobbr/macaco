#include <iostream>
#include <vector>
#include <string>

#include <tuple>
#include <any>
#include <map>
#include <variant>

#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>

#include "treeIndexing.cpp"

//this is the main cpp file which imports the tree_indexing functions and is compiled into a shared library.
//Here is a list of operations it will generate for python macaco.py:
//insert(column_name, array_values): inserts a new column
//remove(column_name): deletes a specific column
//tolist(column_name): shows list of values from a specific column
//locateCel(column_name): shows value from a specific cell
//locateRow(column_name): shows list of values from a specific row
//toIndxCol(column): indexes column values using optimization algorithm from Binary-Search Tree
//show(): shows all table data in a way very similar to pandas dataframe
//plot(columnA, columnB): plots a 2d graphic using data from 2 columns


struct dfbuild{
    std::map<std::string, std::vector<int>> col_int;
    std::map<std::string,std::vector<double>> col_double;
    std::map<std::string,std::vector<std::string>> col_string;
    std::map<std::string,treeIndexing<int>> int_trees;
    std::map<std::string,treeIndexing<double>> double_trees;
    std::map<std::string,treeIndexing<std::string>> string_trees;
    void insertColInt(std::string col_name,  boost::python::list& l){
    std::vector<int> X;
    int token;
    for (int i = 0; i < len(l);){
        token = boost::python::extract<int>(l[i++]);
        X.push_back(token);
        }
    col_int[col_name] = X;
    }
    
    
    
    void insertColDbl(std::string col_name,  boost::python::list& l){
    std::vector<double> X;
    double token;
    for (int i = 0; i < len(l);){
        token = boost::python::extract<double>(l[i++]);
        X.push_back(token);
        }
    col_double[col_name] = X;
    }

    
    
    void insertColStr(std::string col_name,  boost::python::list& l){
    std::vector<std::string> X;
    std::string token;
    for (int i = 0; i < len(l);){
        token = boost::python::extract<std::string>(l[i++]);
        X.push_back(token);
        }
    col_string[col_name] = X;
    }
    
    
    
    void removeColInt(std::string col_name,  boost::python::list& l){
    col_int.erase(col_name);
    }
    
    

    void removeColDbl(std::string col_name,  boost::python::list& l){
        col_double.erase(col_name);
    }



    void removeColStr(std::string col_name,  boost::python::list& l){
        col_string.erase(col_name);
    }



    boost::python::list locateColInt(std::string col_name){
        boost::python::list l;
        for (auto i: col_int[col_name])    {
            l.append(i);
        }
        return l;
    }



    boost::python::list locateColDbl(std::string col_name){
        boost::python::list l;
        for (auto i: col_double[col_name])    {
            l.append(i);
        }
        return l;
    }



    boost::python::list locateColStr(std::string col_name){
        boost::python::list l;
        for (auto i: col_string[col_name])    {
            l.append(i);
        }
        return l;
    }



    boost::python::list locateRowInt(std::string col_name,  boost::python::list & rows){
        int row;
        boost::python::list result;
        for (int i = 0; i < len(rows) ;){
            row = boost::python::extract<int>(rows[i++]);
            result.append(col_int[col_name][row]);
        }
        return result;
    }



    boost::python::list locateRowDbl(std::string col_name,  boost::python::list & rows){
        int row;
        boost::python::list result;
        for (int i = 0; i < len(rows) ;){
            row = boost::python::extract<int>(rows[i++]);
            result.append(col_double[col_name][row]);
        }
        return result;
    }



    boost::python::list locateRowStr(std::string col_name,  boost::python::list & rows){
        int row;
        boost::python::list result;
        for (int i = 0; i < len(rows) ;){
            row = boost::python::extract<int>(rows[i++]);
            result.append(col_string[col_name][row]);
        }
        return result;
    }



    void insertRowInt(std::string col_name,  boost::python::list& l){
        for (int i = 0; i < len(l) ;){
               col_int[col_name].push_back(boost::python::extract<int>(l[i++]));
           }
    }



    void insertRowDbl(std::string col_name,  boost::python::list& l){
        for (int i = 0; i < len(l) ;){
               col_double[col_name].push_back(boost::python::extract<double>(l[i++]));
           }
    }



    void insertRowStr(std::string col_name,  boost::python::list& l){
        for (int i = 0; i < len(l) ;){
               col_string[col_name].push_back(boost::python::extract<std::string>(l[i++]));
           }
    }



    void toIndxColInt(std::string col_name,  boost::python::list & l){
        treeIndexing<int> tree;
        for (int i = 0; i < col_int[col_name].size(); i)    {
            tree.insertRow(col_int[col_name][i],i++);
        }
        int_trees[col_name] = tree;
    }



    void toIndxColDbl(std::string col_name,  boost::python::list & l){
        treeIndexing<double> tree;
        for (int i = 0; i < col_double[col_name].size(); i)    {
            tree.insertRow(col_double[col_name][i],i++);
        }
        double_trees[col_name] = tree;
    }



    void toIndxColStr(std::string col_name,  boost::python::list & l){
        treeIndexing<std::string> tree;
        for (int i = 0; i < col_string[col_name].size(); i)    {
            tree.insertRow(col_string[col_name][i],i++);
        }
        string_trees[col_name] = tree;
    }



    boost::python::list GetNodeRowsInt(std::string col_name,  boost::python::list & nodes){
        boost::python::list result;
        int X;
        std::set<int> Y;
        std::vector<int> partial;
        for (int i = 0; i < len(nodes) ;){
            X = boost::python::extract<int>(nodes[i++]);
            Y = int_trees[col_name].locateRow(X);
            partial.insert(partial.end(), Y.begin(), Y.end());
        }
        for (int i = 0; i < partial.size() ;)    {
            result.append(partial[i++]);
        }
        return result;
    }



    boost::python::list GetNodeRowsDbl(std::string col_name,  boost::python::list & nodes){
        boost::python::list result;
        double X;
        std::set<int> Y;
        std::vector<int> partial;
        for (int i = 0; i < len(nodes) ;){
            X = boost::python::extract<double>(nodes[i++]);
            Y = double_trees[col_name].locateRow(X);
            partial.insert(partial.end(), Y.begin(), Y.end());
        }
        for (int i = 0; i < partial.size() ;)    {
            result.append(partial[i++]);
        }
        return result;
    }



    boost::python::list GetNodeRowsStr(std::string col_name,  boost::python::list & nodes){
        boost::python::list result;
        std::string X;
        std::set<int> Y;
        std::vector<int> partial;
        for (int i = 0; i < len(nodes) ;){
            X = boost::python::extract<std::string>(nodes[i++]);
            Y = string_trees[col_name].locateRow(X);
            partial.insert(partial.end(), Y.begin(), Y.end());
        }
        for (int i = 0; i < partial.size() ;)    {
            result.append(partial[i++]);
        }
        return result;
    }
};


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(dfbuild) {
	class_<dfbuild>("dfbuild",init<>())
	.def("insertColInt", &dfbuild::insertColInt)
	.def("locateColInt", &dfbuild::locateColInt)
	.def("removeColInt", &dfbuild::removeColInt)
	.def("locateRowInt", &dfbuild::locateRowInt)
	.def("insertRowInt", &dfbuild::insertRowInt)
	.def("toIndxColInt", &dfbuild::toIndxColInt)
	.def("insertColDbl", &dfbuild::insertColDbl)
	.def("locateColDbl", &dfbuild::locateColDbl)
	.def("removeColDbl", &dfbuild::removeColDbl)
	.def("locateRowDbl", &dfbuild::locateRowDbl)
	.def("insertRowDbl", &dfbuild::insertRowDbl)
	.def("toIndxColDbl", &dfbuild::toIndxColDbl)
	.def("insertColStr", &dfbuild::insertColStr)
	.def("locateColStr", &dfbuild::locateColStr)
	.def("removeColStr", &dfbuild::removeColStr)
	.def("locateRowStr", &dfbuild::locateRowStr)
	.def("insertRowStr", &dfbuild::insertRowStr)
	.def("toIndxColStr", &dfbuild::toIndxColStr)
	.def("GetNodeRowsInt", &dfbuild::GetNodeRowsInt)
	.def("GetNodeRowsDbl", &dfbuild::GetNodeRowsDbl)
	.def("GetNodeRowsStr", &dfbuild::GetNodeRowsStr)
	.def_readwrite("col_int", &dfbuild::col_int)
    ;
}