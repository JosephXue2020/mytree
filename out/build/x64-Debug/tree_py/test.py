import time

import mytree
print(dir(mytree))

# 测试Node
# class T:
#     def __init__(self):
#         pass

# obj = T()
# n1 = mytree.Node("n1", "string")
# print(n1.identifier())
# print(n1.data())

# # 测试Tree
# obj = mytree.Tree('root', 0, True)
# print(obj.isRoot())
# print(obj.isLeaf())
# print(obj.identifier())
# print(obj.search('root'))
# print(obj.search('root').identifier())
# print(obj)

# 插入数据
print()
obj = mytree.Tree('root', 0, True)
t1 = mytree.Tree('a',1,False)
t1 = obj.insert(t1)
t2 = mytree.Tree('b',2,False)
obj.insert(t2)
t3 = mytree.Tree('c',3,False)
t3 = t2.insert(t3)
t4 = mytree.Tree('d',4,False)
t4 = t3.insert(t4)

for i in range(5):
    temp = mytree.Tree(str(i), i,False)
    obj.insert(temp)

# time.sleep(1)
print('打印obj:',obj)
#print([i.identifier() for i in obj.branch('d')])
#print('traverse:', obj.traverse())

# input()