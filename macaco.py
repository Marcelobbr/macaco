from dfbuild import *
import matplotlib.pyplot as plt

class dataframe():
    def __init__(self,dados=None):
        self.df      = dfbuild()
        self.columns = {}
        self.shape   = [0,0]
        self.indexes = []

        if dados != None:
            for col in dados:
                self.insert(dados[col],str(col))

    def insert(self,array_values,column):
        for col_type in ['int', 'dbl']:
            if col_type == 'dbl':
                inst_type = '(int,float)'
            else: inst_type = col_type
            
            if all(isinstance(x, eval(inst_type)) for x in array_values):
                eval('self.df.insertCol{}(array_values,column)'.format(col_type[0].upper()+col_type[1:]))
                self.columns[column] = col_type
                if self.shape == [0,0]:
                    self.shape[0] = len(array_values)
                self.shape[1] += 1

        if any(isinstance(x, str) for x in array_values):
            self.df.insertColStr(array_values,column)
            self.columns[column]  ='str'
            if self.shape == [0,0]:
                self.shape[0] = len(array_values)
            self.shape[1] += 1

    def remove(self,column):
        for col_type in ['int', 'dbl', 'str']:
            if self.columns[column] == col_type:
                eval('self.df.removeCol{}([],column)'.format(col_type[0].upper()+col_type[1:]))
                self.columns.pop(column)
                self.shape[1] = self.shape[1] - 1
                break
                
    def tolist(self,column):
        for col_type in ['int', 'dbl', 'str']:
            if self.columns[column] == col_type:
                return eval('self.df.locateCol{}(column)'.format(col_type[0].upper()+col_type[1:]))

    def locateCel(self,linha, column):
        linhas = []
        if type(linha) == int:
            linhas.append(linha)
        else:
            linhas = list(linha)
        for col_type in ['int', 'dbl', 'str']:
            if self.columns[column] == col_type:
                return eval('self.df.locateRow{}(linhas, column)'.format(col_type[0].upper()+col_type[1:]))

    def locateRow(self, linha):
        resultado = {k: [] for k in self.columns}
        for column in self.columns:
            resultado[column].append(self.locateCel(linha, column))
        return resultado    

    def insertRow(self,value):
        num_linhas = [len(value[i]) for i in value][0]
        for column in self.columns:
            if self.columns[column] == 'int':
                self.df.insertRowInt(value[column],column)
            elif self.columns[column] == 'dbl':
                self.df.insertRowDbl(value[column],column)
            elif self.columns[column] == 'str':
                self.df.insertRowStr(value[column],column)
        self.shape[0] += num_linhas

    def toIndxCol(self, column):
        for col_type in ['int', 'dbl', 'str']:
            if self.columns[column] == col_type:
                eval('self.df.toIndxCol{}([], column)'.format(col_type[0].upper()+col_type[1:]))
                self.indexes.append(column)

    def Query_Valor(self, val,column):
        if self.columns[column] == 'int':
            return self.df.GetNodeRowsInt(val, column)
        elif self.columns[column] == 'dbl':
            return self.df.GetNodeRowsDbl(val, column)
        elif self.columns[column] == 'str':
            return self.df.GetNodeRowsStr(val, column)

    def show(self):
        data_all = self.locateRow(range(0,self.shape[0]))
        print ('|      {:<10}'.format('index'), sep='', end =" ")
        for header in data_all.keys():
            print ('|      {:<10}'.format(header), sep='', end =" ")
        print(end ="\n")
        for i in range(len(data_all.items())+1):
            print('|      {:<10}'.format(i), end =" ")
            for v in data_all.values():
                print('|      {:<10}'.format(v[0][i]), end =" ")
            print(end ="\n")  
            
    def plot(self, a, b):
        if self.columns[a] in ['int', 'dbl'] and self.columns[b] in ['int', 'dbl']:
            list_a = self.tolist(a)
            list_b = self.tolist(b)
            plt.plot(list_a,list_b)
        else:
            raise ValueError('Some of your selected columns has string type.')