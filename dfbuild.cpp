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
    std::map<std::string, std::vector<int>> cInt;
    std::map<std::string,std::vector<double>> cDbl;
    std::map<std::string,std::vector<std::string>> cStr;
    std::map<std::string,treeIndexing<int>> tInt;
    std::map<std::string,treeIndexing<double>> tDbl;
    std::map<std::string,treeIndexing<std::string>> tStr;
    void insertColInt(std::string col_name,  boost::python::list& listA)
    {
    std::vector<int> X; int element;
    for (int i = 0; i < len(listA);){
        element = boost::python::extract<int>(listA[i++]);
        X.push_back(element);
        }
    cInt[col_name] = X;
    }
    
    
    
    void insertColDbl(std::string col_name,  boost::python::list& listA)
    {
    std::vector<double> X; double element;
    for (int i = 0; i < len(listA);){
        element = boost::python::extract<double>(listA[i++]);
        X.push_back(element);
        }
    cDbl[col_name] = X;
    }

    
    
    void insertColStr(std::string col_name,  boost::python::list& listA)
    {
    std::vector<std::string> X; std::string element;
    for (int i = 0; i < len(listA);){
        element = boost::python::extract<std::string>(listA[i++]);
        X.push_back(element);
        }
    cStr[col_name] = X;
    }
    
    
    
    void removeColInt(std::string col_name)
    {
    cInt.erase(col_name);
    }
    
    

    void removeColDbl(std::string col_name)
    {
        cDbl.erase(col_name);
    }



    void removeColStr(std::string col_name)
    {
        cStr.erase(col_name);
    }



    boost::python::list locateColInt(std::string col_name)
    {
        boost::python::list listA;
        for (auto i: cInt[col_name])    {
            listA.append(i);
        }
        return listA;
    }



    boost::python::list locateColDbl(std::string col_name)
    {
        boost::python::list listA;
        for (auto i: cDbl[col_name])    {
            listA.append(i);
        }
        return listA;
    }



    boost::python::list locateColStr(std::string col_name)
    {
        boost::python::list listA;
        for (auto i: cStr[col_name])    {
            listA.append(i);
        }
        return listA;
    }



    boost::python::list locateRowInt(std::string col_name,  boost::python::list & rows)
    {
        int row; boost::python::list result;
        for (int i = 0; i < len(rows) ;){
            row = boost::python::extract<int>(rows[i++]);
            result.append(cInt[col_name][row]);
        }
        return result;
    }



    boost::python::list locateRowDbl(std::string col_name,  boost::python::list & rows)
    {
        int row; boost::python::list result;
        for (int i = 0; i < len(rows) ;){
            row = boost::python::extract<int>(rows[i++]);
            result.append(cDbl[col_name][row]);
        }
        return result;
    }



    boost::python::list locateRowStr(std::string col_name,  boost::python::list & rows)
    {
        int row; boost::python::list result;
        for (int i = 0; i < len(rows) ;){
            row = boost::python::extract<int>(rows[i++]);
            result.append(cStr[col_name][row]);
        }
        return result;
    }







    void toIndxColInt(std::string col_name)
    {
        treeIndexing<int> bst;
        for (int i = 0; i < cInt[col_name].size(); )    {
            bst.insertRow(cInt[col_name][i],i++);
        }
        tInt[col_name] = bst;
    }



    void toIndxColDbl(std::string col_name)
    {
        treeIndexing<double> bst;
        for (int i = 0; i < cDbl[col_name].size(); )    {
            bst.insertRow(cDbl[col_name][i],i++);
        }
        tDbl[col_name] = bst;
    }



    void toIndxColStr(std::string col_name)
    {
        treeIndexing<std::string> bst;
        for (int i = 0; i < cStr[col_name].size(); )    {
            bst.insertRow(cStr[col_name][i],i++);
        }
        tStr[col_name] = bst;
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
	.def("toIndxColInt", &dfbuild::toIndxColInt)
	.def("insertColDbl", &dfbuild::insertColDbl)
	.def("locateColDbl", &dfbuild::locateColDbl)
	.def("removeColDbl", &dfbuild::removeColDbl)
	.def("locateRowDbl", &dfbuild::locateRowDbl)
	.def("toIndxColDbl", &dfbuild::toIndxColDbl)
	.def("insertColStr", &dfbuild::insertColStr)
	.def("locateColStr", &dfbuild::locateColStr)
	.def("removeColStr", &dfbuild::removeColStr)
	.def("locateRowStr", &dfbuild::locateRowStr)
	.def("toIndxColStr", &dfbuild::toIndxColStr)
	.def_readwrite("cInt", &dfbuild::cInt)
    ;
}