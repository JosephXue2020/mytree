# coding: utf-8
# date: 20230119

import os
import pickle

# 定义一些常用的函数


def get_direc():
    return os.path.dirname(os.path.abspath(__file__))


def save_pickle(path, obj):
    with open(path, 'wb') as f:
        pickle.dump(obj, f)


def read_pickle(path):
    with open(path, 'rb') as f:
        return pickle.load(f)
    