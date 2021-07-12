cmake_minimum_required(VERSION 3.11)     #cmake 최소 버전 요구 사양
project(diva VERSION 1.0.0)            #프로젝트명 버전
set(CMAKE_CXX_STANDARD 11)    


set(SOURCE_MAIN sources/main.cpp)
add_executable(diva ${SOURCE_MAIN})# 생성할 실행파일 이름 지정

# 서브 디렉토리에 있는 cmakeFiles을 실행시켜줌
add_subdirectory(modules/Sensing)
add_subdirectory(modules/LoggingViz)
add_subdirectory(modules/Test)
