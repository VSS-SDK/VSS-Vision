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

set (VSS_INTERFACE libvss-interface.so)
link_libraries(${GTKMM_LIBRARIES})
link_directories(usr/lib ${GTKMM_LIBRARY_DIRS})
include_directories(usr/local/include)

ADD_LIBRARY(core include/Domain/ColorRange.h include/Interfaces/ICalibrationRepository.h include/Interfaces/ICalibrationWindow.h include/Repositories/CalibrationRepository.h include/GImage.h include/Windows/Calibration/CalibrationWindow.h include/Core/DirectoryHelper.h src/Domain/Calibration.cpp src/Domain/ColorRange.cpp src/Repositories/CalibrationRepository.cpp src/Core/DirectoryHelper.cpp src/GImage.cpp src/Windows/Calibration/PartialCalibrationWindowSetup.cpp src/Windows/Calibration/PartialCalibrationWindowEvents.cpp src/Windows/Calibration/PartialCalibrationWindowProcess.cpp include/Domain/ColorType.h include/Domain/ConfigurationType.h include/Core/StringHelper.h src/Core/StringHelper.cpp include/Domain/CutType.h include/Domain/Point2d.h src/Domain/Point2d.cpp src/Domain/ColorType.cpp include/Domain/ColorSpace.h include/Interfaces/ICalibrationBuilder.h include/Builders/CalibrationBuilder.h src/Builders/CalibrationBuilder.cpp include/Interfaces/IImageInputReader.h include/CameraReader.h src/CameraReader.cpp include/Interfaces/IColorRecognizer.h include/ColorRecognizer.h src/ColorRecognizer.cpp include/ImageFileReader.h src/ImageFileReader.cpp include/Core/FrameHelper.h src/Core/FrameHelper.cpp include/Windows/Menu/MenuWindow.h src/Windows/Menu/PartialMenuWindowEvents.cpp src/Windows/Menu/PartialMenuWindowProcess.cpp src/Windows/Menu/PartialMenuWindowSetup.cpp include/Windows/Vision/VisionWindow.h src/Windows/Vision/PartialVisionWindowEvents.cpp src/Windows/Vision/PartialVisionWindowProcess.cpp src/Windows/Vision/PartialVisionWindowSetup.cpp)
ADD_EXECUTABLE(vss-vision src/main.cpp)

TARGET_LINK_LIBRARIES(vss-vision ${VSS_INTERFACE} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${GTKMM_LIBRARIES} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(vss-vision LINK_PUBLIC ${Boost_LIBRARIES} core)

SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")

if(TESTS)

    enable_testing()

    # Process the CMakeLists.txt in third-party/googletest, sets project(gtest) and
    # project(gmock), gives access to ${gtest_SOURCE_DIR} and ${gmock_SOURCE_DIR}.
    add_subdirectory(third-party/googletest)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

    # Tests. *-test.cpp should be added here.
    add_executable(tests
            ./test/Core/StringHelperTests.cpp)

    # Link core, pthread and gtest to tests.
    target_link_libraries(tests
            pthread
            gtest
            gtest_main
            core)

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
