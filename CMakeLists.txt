CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
set(CMAKE_BUILD_TYPE Release)

PROJECT(vss-vision)

find_package(PkgConfig)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)
find_package( OpenCV REQUIRED )

include_directories(${PROTOBUF_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${GTKMM_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
include_directories(src src/Helpers src/Domain src/Repositories src/Core src/Builders src/Windows src/Windows/Calibration src/Windows/Menu src/Windows/Vision)
include_directories(include include/Helpers include/Interfaces include/Domain include/Repositories include/Core include/Builders include/Windows include/Windows/Calibration include/Windows/Menu include/Windows/Vision)

set (VSS_CORE /usr/lib/libvss-core.so)
link_libraries(${GTKMM_LIBRARIES})
link_directories(/usr/lib ${GTKMM_LIBRARY_DIRS})
include_directories(usr/local/include)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INCLUDE include/*.h)

ADD_LIBRARY(vss-vision-core ${SRC} ${INCLUDE})
TARGET_LINK_LIBRARIES(vss-vision-core LINK_PUBLIC ${VSS_CORE} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${GTKMM_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES})

ADD_EXECUTABLE(vss-vision src/main.cpp)
TARGET_LINK_LIBRARIES(vss-vision vss-vision-core)

SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")

SET(VSS_FILES_FOLDER $ENV{HOME}/.vss-files)

# copying vss-vision files to ~/.vss-files
FILE(INSTALL ${CMAKE_HOME_DIRECTORY}/glade/ DESTINATION ${VSS_FILES_FOLDER}/glade)
FILE(INSTALL ${CMAKE_HOME_DIRECTORY}/mock/ DESTINATION ${VSS_FILES_FOLDER}/mock)
FILE(INSTALL ${CMAKE_HOME_DIRECTORY}/data/ DESTINATION ${VSS_FILES_FOLDER}/data)

IF(RELEASE)
    SET(CMAKE_CXX_FLAGS "-Wall -Werror -o2 -std=c++11 -pthread")

    INCLUDE(CPack)

    INSTALL(TARGETS vss-vision DESTINATION bin)

    SET(CPACK_GENERATOR "DEB")
    SET(CPACK_DEBIAN_PACKAGE_NAME "vss-vision")
    SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A Computer Vision System made for Recognize and tracking robots and ball of competition of Robot Soccer IEEE Very Small Size")
    SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
    SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
ELSE()
    INCLUDE_DIRECTORIES(third-party)

    enable_testing()

    add_subdirectory(third-party/googletest)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

    file(GLOB_RECURSE TEST test/*.cpp)

    ADD_EXECUTABLE(tests ${TEST})

    target_link_libraries(tests
            pthread
            gtest
            gtest_main
            vss-vision-core
            ${OpenCV_LIBS})

    SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")
ENDIF()


