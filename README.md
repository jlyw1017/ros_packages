# ros_packages Ros python包新手教程，中文见后
It is a tutorial for build ros packages.

# ros_python_template

build python packages.
In ROS we also use Distutils to create a package(It is ok if you are not familier with that),but there are slightly differences. We don't install the package in the OS but under catkin, but still we use setup.py

Example for the package:   
1.create package.  
  mkdir src  
  under src  
  catkin_create_pkg python_package std_msgs rospy roscpp  sensor_msgs cv_bridge message_filters      
2.Uncomment the following lines in the cmakelist under package root.  
  catkin_python_setup  
  this makes camke execute setup.py, and different from run it directly,but install everything in catkin_ws
  for more ditals see
  http://docs.ros.org/api/catkin/html/user_guide/setup_dot_py.html  
3.Uncomment the following lines in the cmakelist under package root.   
 install(PROGRAMS    
   scripts/my_python_script    
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}    
 )    
 to install the executables 
 for details see:
  http://docs.ros.org/melodic/api/catkin/html/howto/format2/installing_python.html  

4.create setup.py under the package.  
    how to create it, depends on the structure of your package
    https://docs.python.org/2/distutils/examples.html  
    https://docs.python.org/2/distutils/setupscript.html  
e.g
import python_imapro_package.imapro  
if __name__ == '__main__':  
    python_imapro_package.imapro.imagetovedio()  

应邀搞个新手ros教程（完全新手请先看ros官网的docu）也想自己留存一些模板，希望大家提宝贵意见以及纠错&对程序改进  

从零创建新python包  ：

ros环境下编译python的说明：  
    ros下面我们其实也是使用了Distutils来做python包的（不熟悉这个也无所谓，可以google下Distutils有个概念），不过有些区别  
    我们并不把安装的对象安装到系统里，而是安装在catkin下，但是依然使用setup.py  

下面举例具体说明  
1.创建package  
    mkdir src  
    并在src下面  
    catkin_create_pkg python_package std_msgs rospy roscpp  sensor_msgs cv_bridge message_filters  
2.取消packge根目录下，cmakelist里catkin_python_setup的注释  
    这里使得cmake执行setup.py的安装，并且不同于直接运行，而是安装在catkin里恰当的位置  
    说明如下  
http://docs.ros.org/api/catkin/html/user_guide/setup_dot_py.html  
3.取消packge根目录下，cmakelist里  
 install(PROGRAMS  
   scripts/my_python_script  
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}  
 )  
的注释来安装可执行文件  
说明见下  
http://docs.ros.org/melodic/api/catkin/html/howto/format2/installing_python.html  
ros的可执行文件，不是在整体的catkin下面，这样避免冲突。  
标准的ros规范是把可执行的（rosrun的东西）放在/node或者/script下面，不带.py的后缀,避免在rosrun的时候打后缀。  


4.现在我们来创建一个python包(不是ros包，或者说从属于ros包的python包)  
    需要一个setup.py放在和cmakelist同样的文件夹下，其余的和普通的python包区别不大。  
    这里简单介绍下  
    如何编写setup.py其实取决于你想往哪放这个包（或者不要包就是几个py文件） 
    说明和举例见  
    https://docs.python.org/2/distutils/examples.html  
    https://docs.python.org/2/distutils/setupscript.html  

重点1：   
package_dir={'': 'src'}指的是把root放在src这个文件夹下。这要找modules和package会在src这个文件夹下找  
packages=['python_Imapro_package'] 则是说我这个包叫python_Imapro_package，你需要干的事情就是在root（这里是src）下建立一个文件夹叫python_Imapro_package。里面是包的内容  

重点2：  
python_imapro_package 下面要放一个空的叫__init__.py的东西，这个是说，大家好我是包。  
然后在 python_imapro_package 下面放你写的东西就好了  
可以在cmakelist目录下再建一个node文件夹，里面放可执行的.py文件，在这个文件里调用src下面的包。  

如：  
import python_imapro_package.imapro  
if __name__ == '__main__':  
    python_imapro_package.imapro.imagetovedio()  

# ros_package_cpp
第一步创建包
mkdir catkin_ws  
cd catkin_ws  
mkdir src   
cd src  
catkin_create_pkg cpp_package std_msgs rospy roscpp sensor_msgs cv_bridge message_filters  

第二步修改cmakelist
# An example for cmakelist
ros的cmakelist和普通的区别不大，这里再简单说明下
cmake_minimum_required(VERSION 2.8.3) 

project(nodename) 

1. 找到需要的依赖
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  message_filters
  roscpp
  rospy
  sensor_msgs
  std_msgs
  pcl_ros 
  tf2_ros
)
find_package(OpenCV REQUIRED)     //opencv必须单独写 

2. System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)  //boost 必须单独写

3. 产生这个包的信息，使得其他包和后面的函数能用这个包的信息
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES cpp_package
  CATKIN_DEPENDS cv_bridge message_filters roscpp rospy sensor_msgs std_msgs
  DEPENDS system_lib
)

4 告诉编译器我的include位置，放你的.hpp文件
 同时include的时候，不用给出相对路径位置了，会直接搜索include文件夹
 Specify additional locations of header files
 Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} 
)

5 声明引用的其他cpp，一般是hpp中函数的实现
 Declare a C++ library
 add_library(${PROJECT_NAME}
   src/${PROJECT_NAME}/cpp_functions.cpp
 )

6 声明其他依赖
 Add cmake target dependencies of the executable
 same as for the library above
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

7 把上面的lib链接到execu
 Specify libraries to link a library or executable target against
 target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )


举例
add_executable(foo src/foo.cpp)
add_library(moo src/moo.cpp)
target_link_libraries(foo moo)  -- This links foo against libmoo.so
