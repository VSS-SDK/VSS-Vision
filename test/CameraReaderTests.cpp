//
// Created by johnathan on 16/03/18.
//

#include "gtest/gtest.h"
#include "CameraReader.h"

TEST(CameraReader_Constructor, WhenBuildObject_ShouldHaveRightParametersValue){
  auto sut = new CameraReader();

  EXPECT_EQ(sut->getCapture().isOpened(), false);
}

TEST(CameraReader_getAllPossibleSources, WhenGetAllPossibleSources_ShouldReturnZeroMocked_TODO){
  auto sut = new CameraReader();
  auto allPossibleSources = sut->getAllPossibleSources();

  EXPECT_EQ(allPossibleSources.size(), 1);
  EXPECT_EQ(allPossibleSources.at(0), "0");
}

TEST(CameraReader_setSource, WhenTryToSetANotANumValue_ShouldNotSetActualCameraIndex){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setSource("NAN - Not a Num"));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] Invalid camera index\n", output.c_str());
}

TEST(CameraReader_setSource, WhenTryToSetAInvalidValue_ShouldNotSetActualCameraIndex){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setSource("123"));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] Invalid camera index\n", output.c_str());

}

TEST(CameraReader_setSource, WhenTryToSetAnAvailableValue_ShouldSetActualCameraIndex){
  auto sut = new CameraReader();

  sut->setSource("0");
}

TEST(CameraReader_initializeReceivement, WhenTryToInitializeReceivementWithoutACamera_ShouldCerranError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  sut->initializeReceivement();
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] Invalid camera index\n", output.c_str());
}

TEST(CameraReader_isAValidCameraIndex, WhenIsLessThanZeroShouldReturnFalse){
  auto sut = new CameraReader();

  EXPECT_FALSE(sut->isAValidCameraIndex(-1));
}

TEST(CameraReader_isAValidCameraIndex, WhenIsAnInvalidIndexShouldReturnFalse){
  auto sut = new CameraReader();

  EXPECT_FALSE(sut->isAValidCameraIndex(11111));
}

TEST(CameraReader_isAValidCameraIndex, WhenIsAValidVShouldReturnTrue){
  auto sut = new CameraReader();

  EXPECT_TRUE(sut->isAValidCameraIndex(0));
}
