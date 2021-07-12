find_package( Threads )
find_package(cppzmq)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "../../service/protobuf/sensors.proto" )

include_directories(../../service headers sources)
set(SOURCE_sensing 
    sources/main.cpp 
    sources/CamSensingThread.cpp 
)
add_executable(sensing ${SOURCE_sensing} 
    ${PROTO_SRCS} ${PROTO_HDRS}                 # Google Protocol Buffer
    ${OpenCV_INCLUDE_DIRS}                      # OpenCV
)

target_link_libraries(sensing PUBLIC 
    cppzmq
    ${OpenCV_LIBS}                  # OpenCV
    ${PROTOBUF_LIBRARIES}           # Google Protocol Buffer
) 