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

# # 插入数据
# print()
# t1 = mytree.Tree('a',1,False)
# obj.insert(t1)
# t2 = mytree.Tree('b',1,False)
# obj.insert(t2)
# t3 = mytree.Tree('c',1,False)
# t2.insert(t3)
# print(obj)
# print(obj.branch('c'))
# print('traverse:', obj.traverse())

print(mytree.Node("n1", "string").data() + mytree.Node("n2", "string").data())
print(mytree.Node("n1", 3).data() + mytree.Node("n2", 9).data())