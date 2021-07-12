find_package( Threads )
find_package(cppzmq)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 

include_directories(../../service headers sources)
set(SOURCE_TEST 
    sources/main.cpp
)

add_executable(test_ex 
    ${SOURCE_TEST} 
    ${OpenCV_INCLUDE_DIRS}                      
)

target_link_libraries(test_ex 
    PUBLIC 
    cppzmq
    ${OpenCV_LIBS}                 
) 


