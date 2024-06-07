cmake_minimum_required (VERSION 3.8)
 
# 添加python和pybind11路径
set(PYTHONPATH C:/anaconda3)
set(PYBINDPATH D:/CPPCode/extern/pybind11)
 
# 添加头文件
include_directories(${PYTHONPATH}/include ${PYBINDPATH}/include)
 
# 生成动态库
add_library(mytree SHARED mytree.cpp)
 
# 后缀名改成pyd能够被python引用
set_target_properties(mytree PROPERTIES SUFFIX ".pyd")
 
# 添加python静态库
target_link_libraries(mytree ${PYTHONPATH}/libs/python310.lib) 