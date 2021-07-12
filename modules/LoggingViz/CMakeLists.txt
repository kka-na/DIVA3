set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
set(CMAKE_AUTOUIC ON) # UI files

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED Widgets Gui)
set(Qt5SerialBus_DIR /home/kanakim/qtserialbus/lib/cmake/Qt5SerialBus)
link_directories(${Qt5SerialBus_DIR}) 
find_package(Qt5 REQUIRED COMPONENTS Quick Core Gui Sql X11Extras OpenGL Network PrintSupport WebEngineWidgets SerialPort SerialBus Charts)
find_package(Protobuf REQUIRED)
find_package(Qt5QuickCompiler)


set(QWT_INCLUDE_DIR /usr/local/qwt-6.2.0-rc2/include)
set ( QWT_INCLUDE_DIRS ${QWT_INCLUDE_DIR} )

# version
set ( _VERSION_FILE ${QWT_INCLUDE_DIR}/qwt_global.h )
if ( EXISTS ${_VERSION_FILE} )
  file ( STRINGS ${_VERSION_FILE} _VERSION_LINE REGEX "define[ ]+QWT_VERSION_STR" )
  if ( _VERSION_LINE )
    string ( REGEX REPLACE ".*define[ ]+QWT_VERSION_STR[ ]+\"([^\"]*)\".*" "\\1" QWT_VERSION_STRING "${_VERSION_LINE}" )
  endif ()
endif ()
unset ( _VERSION_FILE )

find_library ( QWT_LIBRARY
  NAMES qwt 
  HINTS /usr/local/qwt-6.2.0-rc2/lib
)
set ( QWT_LIBRARIES ${QWT_LIBRARY} )

include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Qwt REQUIRED_VARS QWT_LIBRARY QWT_INCLUDE_DIR VERSION_VAR QWT_VERSION_STRING )

if (Qwt_FOUND AND NOT TARGET Qwt::Qwt)
  add_library(Qwt::Qwt UNKNOWN IMPORTED)
  set_target_properties(Qwt::Qwt PROPERTIES
                        INTERFACE_INCLUDE_DIRECTORIES "${QWT_INCLUDE_DIRS}"
                        IMPORTED_LOCATION "${QWT_LIBRARIES}")
endif ()

mark_as_advanced (
  QWT_LIBRARY
  QWT_INCLUDE_DIR
)
include_directories(${QWT_INCLUDE_DIR})

find_package( Threads )
find_package(cppzmq)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "../../service/protobuf/sensors.proto" )




include_directories(../../service include sources headers forms include/resource include/widgets)


set(HEADER_sensors
    headers/CamLogVizThread.h
    headers/CanLogVizThread.h
)
set(SOURCE_sensors 
    sources/CamLogVizThread.cpp
    sources/CanLogVizThread.cpp
) 
set(SOURCE_widgets
   include/widgets/SpeedoMeter.cpp
)

set(HEADER_ui
    headers/mainwindow.h 
    headers/informdialog.h
)

set(SOURCE_ui
    sources/mainwindow.cpp
    sources/informdialog.cpp
)

set(SOURCE_loggingviz 
    ${SOURCE_sensors}
    ${SOURCE_widgets}
    sources/main.cpp  
    ${SOURCE_ui}
)

qt5_wrap_cpp(HEADER_loggingviz ${HEADER_sensors} ${HEADER_ui})
qt5_wrap_ui(UI_loggingviz forms/mainwindow.ui forms/informdialog.ui)
#qt5_add_resources(RS_loggingviz resource/resources.qrc)
qtquick_compiler_add_resources(RESOURCES include/resource/resources.qrc)

add_executable(loggingviz 
    ${SOURCE_loggingviz} ${HEADER_loggingviz} ${UI_loggingviz} ${RESOURCES}
    ${PROTO_SRCS} ${PROTO_HDRS}                 # Google Protocol Buffer
    ${OpenCV_INCLUDE_DIRS}                      # OpenCV
    ${QWT_INCLUDE_DIRS}
)


target_link_libraries(loggingviz PUBLIC 
    cppzmq
    ${OpenCV_LIBS}                  # OpenCV
    ${PROTOBUF_LIBRARIES}           # Google Protocol Buffer
    Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::WebEngineWidgets Qt5::OpenGL Qt5::Charts
    ${QWT_LIBRARIES}
) 



