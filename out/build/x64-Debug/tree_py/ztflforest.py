# coding: utf-8
import os
import abc

import pandas as pd

import funcs
import mytree


def new_tree(child_parent_pairs, root_name=''):
    print('开始构建ztfl树...')

    # 字典：{parent:[child,...],...}
    p2c = dict()
    for child, parent in child_parent_pairs:
        if parent in p2c:
            p2c[parent].append(child)
        else:
            p2c[parent] = [child]
    
    root = mytree.Tree(root_name, 0, True)
    buf = [root]
    while len(buf):
        p_node = buf.pop(0)
        parent = p_node.identifier()
        children = p2c.get(parent)
        p_level = p_node.data()
        if children is not None:
            for child in children:
                #print(parent,":",child)
                new_node = mytree.Tree(child, p_level+1, False)
                c_node = p_node.insert(new_node)
                buf.append(c_node)
    return root


# 用接口类约束
class IManager(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def get_name(self):
        pass
    
    @abc.abstractmethod
    def build(self):
        pass
    
    @abc.abstractmethod
    def load(self):
        pass
    
    @abc.abstractmethod
    def cache(self):
        pass


# 具体实现
class TreeManager(IManager):
    def __init__(self, name, file):
        self.name = name
        self.file = file

        self.direc = funcs.get_direc()
    
    def get_name(self):
        return self.name
    
    # df列名标准化
    # XXDM:类别；DM: 父类
    def standardization(self, df):
        return df
    
    def build(self):
        tab_path = os.path.join(self.direc, self.file)
        df = pd.read_excel(tab_path)
        
        # 列名标准化
        df = self.standardization(df)
        
        # 空值填充空串
        df['DM'] = df['DM'].fillna('')
        code_pairs = df[['XXDM', 'DM']].values.tolist()
        tree = new_tree(code_pairs, '')
        return tree
    
    def get_cache_path(self):
        prefix = os.path.splitext(self.file)[0]
        cache_path = os.path.join(self.direc, prefix+'.pkl')
        return cache_path
    
    # 以pickle格式缓存
    def load(self):
        cache_path = self.get_cache_path()
        if not os.path.exists(cache_path):
            raise RuntimeError('cache of tree does not exists')
        return funcs.read_pickle(cache_path)
    
    def cache(self):
        tree = self.build()
        cache_path = self.get_cache_path()
        funcs.save_pickle(cache_path, tree)
        

# 最初使用的树
# 与ztfltree模块返回的树相同
class OriginalTreeManager(TreeManager):
    def __init__(self):
        super().__init__('original', 'ztfl_full.xlsx')


class Forest:
    def __init__(self):
        self.tree_dt = dict()
    
    def regist(self, itree):
        assert isinstance(itree, IManager)
        name = itree.get_name()
        self.tree_dt[name] = itree
    
    # 获取一棵树的实例
    def get(self, name, cache=False):
        if name not in self.tree_dt:
            raise RuntimeError('bad input tree name')
        
        tree = self.tree_dt[name]
        if cache:
            return tree.load()
        return tree.build()
    
    def catalog(self):
        return list(self.tree_dt.keys())
    
    def cache(self, name):
        if name not in self.tree_dt:
            raise RuntimeError('bad input tree name')
        
        tree = self.tree_dt[name]
        tree.cache()
    

# 初始化函数
def init():
    forest = Forest()
    forest.regist(OriginalTreeManager())
    
    return forest
    

# 模块变量
forest = init()
