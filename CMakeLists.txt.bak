cmake_minimum_required(VERSION 3.13)
project(linepass)

set(CMAKE_CXX_STANDARD 14)

include_directories(common)
include_directories(linepass)
include_directories(linepassd)
include_directories(/usr/local/include)
include_directories(/usr/local/mysql/include/)
include_directories(/usr/include/mysql)

link_directories(/usr/local/lib)
link_directories(/usr/local/mysql/lib)
link_libraries(mysqlclient)
add_executable(linepass
        linepass/command.cpp
        linepass/comprogram.cpp
        common/mainprogram.cpp
        common/comline.cpp
        common/link.cpp
        common/threadpool.cpp
        common/logs.cpp
        common/linesecret.cpp
        common/secret.cpp
        linepass/main.cpp)
	
add_executable(linepassd
common/mainprogram.cpp
common/comline.cpp
common/linesecret.cpp
common/threadpool.cpp
common/secret.cpp
common/link.cpp
linepassd/mysqlc.cpp
linepassd/granalysis.cpp
linepassd/mysqlcpool.cpp
linepassd/lineprogram.cpp
linepassd/main.cc)
