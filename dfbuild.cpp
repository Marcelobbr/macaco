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

class dfbuild{
public:
    std::map<std::string, std::vector<int>> col_int;
    std::map<std::string,std::vector<double>> col_double;
    std::map<std::string,std::vector<std::string>> col_string;
    std::map<std::string,treeIndexing<int>> int_trees;
    std::map<std::string,treeIndexing<double>> double_trees;
    std::map<std::string,treeIndexing<std::string>> string_trees;


    void insertColInt(boost::python::list& l, std::string col_name);
    void insertColDbl(boost::python::list& l, std::string col_name);
    void insertColStr(boost::python::list& l, std::string col_name);

    void removeColInt(boost::python::list& l, std::string col_name);
    void removeColDbl(boost::python::list& l, std::string col_name);
    void removeColStr(boost::python::list& l, std::string col_name);

    boost::python::list locateColInt(std::string col_name);
    boost::python::list locateColDbl(std::string col_name);
    boost::python::list locateColStr(std::string col_name);

    void insertRowInt(boost::python::list& l, std::string col_name);
    void insertRowDbl(boost::python::list& l, std::string col_name);
    void insertRowStr(boost::python::list& l, std::string col_name);
	
    boost::python::list locateRowInt(boost::python::list & rows, std::string col_name);
    boost::python::list locateRowDbl(boost::python::list & rows, std::string col_name);
    boost::python::list locateRowStr(boost::python::list & rows, std::string col_name);

    void toIndxColInt(boost::python::list& l, std::string col_name);
    void toIndxColDbl(boost::python::list& l, std::string col_name);
    void toIndxColStr(boost::python::list& l, std::string col_name);

    boost::python::list GetNodeRowsInt(boost::python::list & nodes, std::string col_name);
    boost::python::list GetNodeRowsDbl(boost::python::list & nodes, std::string col_name);
    boost::python::list GetNodeRowsStr(boost::python::list & nodes, std::string col_name);

};

void dfbuild::insertColInt(boost::python::list& l, std::string col_name){
    std::vector<int> w;
    int token;
    for (int i = 0; i < len(l) ; i++){
        token = boost::python::extract<int>(l[i]);
        w.push_back(token);
    }
    col_int[col_name] = w;
}
void dfbuild::insertColDbl(boost::python::list& l, std::string col_name){
    std::vector<double> w;
    double token;
    for (int i = 0; i < len(l) ; i++){
        token = boost::python::extract<double>(l[i]);
        w.push_back(token);
    }
    col_double[col_name] = w;
}
void dfbuild::insertColStr(boost::python::list& l, std::string col_name){
    std::vector<std::string> w;
    std::string token;
    for (int i = 0; i < len(l) ; i++){
        token = boost::python::extract<std::string>(l[i]);
        w.push_back(token);
    }
    col_string[col_name] = w;
}

void dfbuild::removeColInt(boost::python::list& l, std::string col_name){
    col_int.erase(col_name);
}
void dfbuild::removeColDbl(boost::python::list& l, std::string col_name){
    col_double.erase(col_name);
}
void dfbuild::removeColStr(boost::python::list& l, std::string col_name){
    col_string.erase(col_name);
}

boost::python::list dfbuild::locateColInt(std::string col_name){
    boost::python::list l;
    for (auto i: col_int[col_name])
    {
        l.append(i);
    }
    return l;
}
boost::python::list dfbuild::locateColDbl(std::string col_name){
    boost::python::list l;
    for (auto i: col_double[col_name])
    {
        l.append(i);
    }
    return l;
}
boost::python::list dfbuild::locateColStr(std::string col_name){
    boost::python::list l;
    for (auto i: col_string[col_name])
    {
        l.append(i);
    }
    return l;
}

boost::python::list dfbuild::locateRowInt(boost::python::list & rows, std::string col_name){
    boost::python::list result;
    int row;
    for (int i = 0; i < len(rows) ; i++){
        row = boost::python::extract<int>(rows[i]);
        result.append(col_int[col_name][row]);
    }
    return result;
}

boost::python::list dfbuild::locateRowDbl(boost::python::list & rows, std::string col_name){
    boost::python::list result;
    int row;
    for (int i = 0; i < len(rows) ; i++){
        row = boost::python::extract<int>(rows[i]);
        result.append(col_double[col_name][row]);
    }
    return result;
}

boost::python::list dfbuild::locateRowStr(boost::python::list & rows, std::string col_name){
    boost::python::list result;
    int row;
    for (int i = 0; i < len(rows) ; i++){
        row = boost::python::extract<int>(rows[i]);
        result.append(col_string[col_name][row]);
    }
    return result;
}

void dfbuild::insertRowInt(boost::python::list& l, std::string col_name){
    for (int i = 0; i < len(l) ; i++){
           col_int[col_name].push_back(boost::python::extract<int>(l[i]));
       }
}
void dfbuild::insertRowDbl(boost::python::list& l, std::string col_name){
    for (int i = 0; i < len(l) ; i++){
           col_double[col_name].push_back(boost::python::extract<double>(l[i]));
       }
}
void dfbuild::insertRowStr(boost::python::list& l, std::string col_name){
    for (int i = 0; i < len(l) ; i++){
           col_string[col_name].push_back(boost::python::extract<std::string>(l[i]));
       }
}

void dfbuild::toIndxColInt(boost::python::list & l,std::string col_name){
    treeIndexing<int> tree;
    for (int i = 0; i < col_int[col_name].size(); ++i)
    {
        tree.insertRow(col_int[col_name][i],i);
    }
    int_trees[col_name] = tree;
}
void dfbuild::toIndxColDbl(boost::python::list & l,std::string col_name){
    treeIndexing<double> tree;
    for (int i = 0; i < col_double[col_name].size(); ++i)
    {
        tree.insertRow(col_double[col_name][i],i);
    }
    double_trees[col_name] = tree;
}
void dfbuild::toIndxColStr(boost::python::list & l,std::string col_name){
    treeIndexing<std::string> tree;
    for (int i = 0; i < col_string[col_name].size(); ++i)
    {
        tree.insertRow(col_string[col_name][i],i);
    }
    string_trees[col_name] = tree;
}

boost::python::list dfbuild::GetNodeRowsInt(boost::python::list & nodes, std::string col_name){
    std::vector<int> output;
    std::set<int> s;
    int w;
    boost::python::list result;

    for (int i = 0; i < len(nodes) ; i++){
        w = boost::python::extract<int>(nodes[i]);
        s = int_trees[col_name].locateRow(w);
        output.insert(output.end(), s.begin(), s.end());
    }
    for (int i = 0; i < output.size() ; i++)
    {
        result.append(output[i]);
    }
    return result;
}

boost::python::list dfbuild::GetNodeRowsDbl(boost::python::list & nodes, std::string col_name){
    std::vector<int> output;
    std::set<int> s;
    double w;
    boost::python::list result;

    for (int i = 0; i < len(nodes) ; i++){
        w = boost::python::extract<double>(nodes[i]);
        s = double_trees[col_name].locateRow(w);
        output.insert(output.end(), s.begin(), s.end());
    }
    for (int i = 0; i < output.size() ; i++)
    {
        result.append(output[i]);
    }
    return result;
}
boost::python::list dfbuild::GetNodeRowsStr(boost::python::list & nodes, std::string col_name){
    std::vector<int> output;
    std::set<int> s;
    std::string w;
    boost::python::list result;

    for (int i = 0; i < len(nodes) ; i++){
        w = boost::python::extract<std::string>(nodes[i]);
        s = string_trees[col_name].locateRow(w);
        output.insert(output.end(), s.begin(), s.end());
    }
    for (int i = 0; i < output.size() ; i++)
    {
        result.append(output[i]);
    }
    return result;
}


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(dfbuild)
{
	class_<dfbuild>("dfbuild",init<>())
	.def("insertColInt", & dfbuild::insertColInt)
	.def("locateColInt", & dfbuild::locateColInt)
	.def("removeColInt", & dfbuild::removeColInt)
	.def("locateRowInt", & dfbuild::locateRowInt)
	.def("insertRowInt", & dfbuild::insertRowInt)
	.def("toIndxColInt", & dfbuild::toIndxColInt)
	.def("insertColDbl", & dfbuild::insertColDbl)
	.def("locateColDbl", & dfbuild::locateColDbl)
	.def("removeColDbl", & dfbuild::removeColDbl)
	.def("locateRowDbl", & dfbuild::locateRowDbl)
	.def("insertRowDbl", & dfbuild::insertRowDbl)
	.def("toIndxColDbl", & dfbuild::toIndxColDbl)
	.def("insertColStr", & dfbuild::insertColStr)
	.def("locateColStr", & dfbuild::locateColStr)
	.def("removeColStr", & dfbuild::removeColStr)
	.def("locateRowStr", & dfbuild::locateRowStr)
	.def("insertRowStr", & dfbuild::insertRowStr)
	.def("toIndxColStr", & dfbuild::toIndxColStr)
	.def("GetNodeRowsInt", & dfbuild::GetNodeRowsInt)
	.def("GetNodeRowsDbl", & dfbuild::GetNodeRowsDbl)
	.def("GetNodeRowsStr", & dfbuild::GetNodeRowsStr)
	.def_readwrite("col_int", & dfbuild::col_int)
    ;
}