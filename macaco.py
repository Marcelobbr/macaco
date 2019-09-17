from dfbuild import *
import matplotlib.pyplot as plt

class dataframe():
    def __init__(self,initializer=None):
        self.df      = dfbuild()
        self.columns_dict = {}
        self.dimensions   = [0,0]
        self.indexes = []

        if initializer != None:
            for col in initializer:
                self.insert(str(col), initializer[col])

    def summary(self, info="info"):
        if info == "columns":
            result = list(self.columns_dict.keys())
            return result
        if info == "dtypes":
            for k, v in self.columns_dict.items():
                print('{:<5}'.format(k), v)
        if info == "info":
            print("RangeIndex: {} entries, 0 to {}".format(self.dimensions[0], self.dimensions[0]-1))
            print("Data columns (total {} columns):".format(self.dimensions[1]))
            for k, v in self.columns_dict.items():
                print('{}      {} non-null      '.format(k, sum(x is not None for x in self.tolist(k))), v)
            print('dtypes:', end=' ')
            for v in set(self.columns_dict.values()):
                print(v, end=', ')
                
    def check_size(self, array_values):
        if self.dimensions[0] != 0 and self.dimensions[0] != len(array_values):
            raise ValueError("Column size is not compatible with dataframe size.")        
    
    def insert(self,column,  array_values):
        self.check_size(array_values)
        for col_type in ['int', 'dbl']:
            if col_type == 'dbl':
                inst_type = '(int,float)'
            else: inst_type = col_type
            
            if all(isinstance(x, eval(inst_type)) for x in array_values):
                eval('self.df.insertCol{}(column,  array_values)'.format(col_type[0].upper()+col_type[1:]))
                self.columns_dict[column] = col_type
        
        col_type = 'str'
        if any(isinstance(x, eval(col_type)) for x in array_values):
            eval('self.df.insertCol{}(column,  array_values)'.format(col_type[0].upper()+col_type[1:]))
            self.columns_dict[column]  = col_type
            
        if self.dimensions[0] == 0 and self.dimensions[1] == 0:
            self.dimensions[0] = len(array_values)
        self.dimensions[1] = self.dimensions[1] + 1

    def remove(self,column):
        for col_type in ['int', 'dbl', 'str']:
            if self.columns_dict[column] == col_type:
                eval('self.df.removeCol{}(column)'.format(col_type[0].upper()+col_type[1:]))
                self.columns_dict.pop(column)
                self.dimensions[1] = self.dimensions[1] - 1
                break

    def toIndxCol(self, column):
        for col_type in ['int', 'dbl', 'str']:
            if self.columns_dict[column] == col_type:
                eval('self.df.toIndxCol{}(column)'.format(col_type[0].upper()+col_type[1:]))
                if column not in self.indexes:
                    self.indexes.append(column)
                
    def tolist(self,column):
        for col_type in ['int', 'dbl', 'str']:
            if self.columns_dict[column] == col_type:
                column_tolist = eval('self.df.locateCol{}(column)'.format(col_type[0].upper()+col_type[1:]))
                return column_tolist

    def locateCel(self,column,  loc_row):
        loc_rows = []
        if type(loc_row) != int:
            loc_rows = list(loc_row)
        else:
            loc_rows.append(loc_row)
        for col_type in ['int', 'dbl', 'str']:
            if self.columns_dict[column] == col_type:
                cel_val = eval('self.df.locateRow{}(column, loc_rows)'.format(col_type[0].upper()+col_type[1:]))
                return cel_val

    def locateRow(self, loc_row):
        row_query = {}
        for c in self.columns_dict:
            row_query[c] = []
        for column in self.columns_dict:
            row_query[column].append(self.locateCel(column,  loc_row))
        return row_query    

    def show(self, head = 10, col_max = 5):
        data_all = self.locateRow(range(0,self.dimensions[0]))
        print('dataframe is limited to {} rows and {} columns.'.format(head, col_max),'\n')
        print ('|      {:<10}'.format('index'), sep='', end =" ")
        count = 0
        for header in data_all.keys():
            print ('|      {:<10}'.format(header), sep='', end =" ")
            count += 1
            if count == col_max: break
        print(end ="\n")
        count = 0
        for i in range(len(data_all.items())+1):
            print('|      {:<10}'.format(' '), sep='', end =" ")
            count += 1
            if count == col_max: break
        print(end ="\n")
        row_count = 0
        
        for i in range(min(self.dimensions[0], head)):
            print('|      {:<10}'.format(i), end =" ")
            count = 0
            for v in data_all.values():
                print('|      {:<10}'.format(v[0][i]), end =" ")
                count += 1
                if count == col_max: break
            print(end ="\n")  
            
    def plot(self, a, b, how="lineplot"):
        if self.columns_dict[a] in ['int', 'dbl'] and self.columns_dict[b] in ['int', 'dbl']:
            list_a = self.tolist(a)
            list_b = self.tolist(b)
            if how == 'lineplot':
                plt.plot(list_a,list_b)
            elif how == 'scatterplot':
                plt.scatter(list_a,list_b)
            else:
                raise ValueError('Please choose a valid plot type.')
        else:
            raise ValueError('Some of your selected columns has string type.')