PROJECT(vss-vision)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++17 -o2")

find_package(PkgConfig)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
find_package( OpenCV REQUIRED )

include_directories(${PROTOBUF_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${GTKMM_INCLUDE_DIRS})
include_directories(src)
include_directories(include include/Interfaces)

file(GLOB_RECURSE SRC src/*.cpp)

set (VSS_INTERFACE libvss-interface.so)
link_libraries(${GTKMM_LIBRARIES})
link_directories(usr/lib ${GTKMM_LIBRARY_DIRS})
include_directories(usr/local/include)

ADD_EXECUTABLE(vss-vision ${SRC})

TARGET_LINK_LIBRARIES(vss-vision ${VSS_INTERFACE} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${GTKMM_LIBRARIES} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(vss-vision LINK_PUBLIC ${Boost_LIBRARIES})

INSTALL(TARGETS vss-vision DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "vss-vision")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A Computer Vision System made for Recognize and tracking robots and ball of competition of Robot Soccer IEEE Very Small Size")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

INCLUDE(CPack)
