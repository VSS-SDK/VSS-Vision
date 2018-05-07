CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

OPTION(TESTS "build tests" OFF)

PROJECT(vss-vision)

find_package(PkgConfig)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)
find_package( OpenCV REQUIRED )

include_directories(${PROTOBUF_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${GTKMM_INCLUDE_DIRS})
include_directories(src src/Domain src/Repositories src/Core src/Builders src/Windows src/Windows/Calibration src/Windows/Menu src/Windows/Vision)
include_directories(include include/Interfaces include/Domain include/Repositories include/Core include/Builders include/Windows include/Windows/Calibration include/Windows/Menu include/Windows/Vision)

set (VSS_CORE libvss-core.so)
link_libraries(${GTKMM_LIBRARIES})
link_directories(usr/lib ${GTKMM_LIBRARY_DIRS})
include_directories(usr/local/include)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INCLUDE include/*.h)

ADD_LIBRARY(core ${SRC} ${INCLUDE})
ADD_EXECUTABLE(vss-vision src/main.cpp)

TARGET_LINK_LIBRARIES(vss-vision ${VSS_CORE} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${GTKMM_LIBRARIES} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(vss-vision LINK_PUBLIC ${Boost_LIBRARIES} core)

SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")

if(TESTS)

    enable_testing()

    # Process the CMakeLists.txt in third-party/googletest, sets project(gtest) and
    # project(gmock), gives access to ${gtest_SOURCE_DIR} and ${gmock_SOURCE_DIR}.
    add_subdirectory(third-party/googletest)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

    # Tests. *-test.cpp should be added here.
    add_executable(tests
            test/Core/StringHelperTests.cpp test/MainTests.cpp test/CameraReaderTests.cpp test/Builders/CalibrationBuilderTests.cpp test/Repositories/CalibrationRepositoryTests.cpp test/ColorRecognizerTests.cpp)

    # Link core, pthread and gtest to tests.
    target_link_libraries(tests
            pthread
            gtest
            gtest_main
            core
            ${OpenCV_LIBS})

endif()

INSTALL(TARGETS vss-vision DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "vss-vision")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A Computer Vision System made for Recognize and tracking robots and ball of competition of Robot Soccer IEEE Very Small Size")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

INCLUDE(CPack)
