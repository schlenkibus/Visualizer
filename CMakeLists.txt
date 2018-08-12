cmake_minimum_required(VERSION 3.10)
project(VISUALS)

set(CMAKE_CXX_STANDARD 17)


include_directories(C:\\Users\\Stryk\\CLionProjects\\SFML-2.4.0\\include\\)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

link_directories(C:\\Users\\Stryk\\CLionProjects\\SFML-2.4.0\\lib)
add_executable(VISUALS ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(VISUALS pthread)
TARGET_LINK_LIBRARIES(VISUALS stdc++fs)
TARGET_LINK_LIBRARIES(VISUALS sfml-system)
TARGET_LINK_LIBRARIES(VISUALS sfml-audio)
TARGET_LINK_LIBRARIES(VISUALS sfml-graphics)
TARGET_LINK_LIBRARIES(VISUALS sfml-window)
TARGET_LINK_LIBRARIES(VISUALS sfml-network)
TARGET_LINK_LIBRARIES(VISUALS m)