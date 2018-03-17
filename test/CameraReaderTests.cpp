//
// Created by johnathan on 16/03/18.
//

#include "gtest/gtest.h"
#include "CameraReader.h"

TEST(CameraReader_Constructor, WhenBuildObject_ShouldHaveRightParametersValue){
  auto sut = new CameraReader();

  EXPECT_EQ(sut->getRunningCapture(), false);
  EXPECT_EQ(sut->getCamerasIndex().size(), 1);
  EXPECT_EQ(sut->getShouldCloseReader(), false);
  EXPECT_EQ(sut->getActualCameraIndex(), -1);
  EXPECT_EQ(sut->getActualFrame().cols, 0);
  EXPECT_EQ(sut->getActualFrame().rows, 0);
  EXPECT_EQ(sut->getCapture().isOpened(), false);
}

TEST(CameraReader_getAllPossibleSources, WhenGetAllPossibleSources_ShouldReturnZeroMocked_TODO){
  auto sut = new CameraReader();
  auto allPossibleSources = sut->getAllPossibleSources();

  EXPECT_EQ(allPossibleSources.size(), 1);
  EXPECT_EQ(allPossibleSources.at(0), "0");
}

TEST(CameraReader_pause_start, WhenCallPauseAndStart_ShouldTogglerunningCapture){
  auto sut = new CameraReader();

  EXPECT_EQ(sut->getRunningCapture(), false);

  sut->start();
  EXPECT_EQ(sut->getRunningCapture(), true);

  sut->pause();
  EXPECT_EQ(sut->getRunningCapture(), false);
}

TEST(CameraReader_close, WhenCallClose_ShouldSetShouldCloseReaderToTrue){
  auto sut = new CameraReader();

  EXPECT_EQ(sut->getShouldCloseReader(), false);

  sut->close();
  EXPECT_EQ(sut->getShouldCloseReader(), true);
}

TEST(CameraReader_setSource, WhenTryToSetANotANumValue_ShouldNotSetActualCameraIndex){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setSource("NAN - Not a Num"));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] Invalid camera index\n", output.c_str());

  EXPECT_EQ(sut->getActualCameraIndex(), -1);
}

TEST(CameraReader_setSource, WhenTryToSetAInvalidValue_ShouldNotSetActualCameraIndex){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setSource("123"));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] Invalid camera index\n", output.c_str());

  EXPECT_EQ(sut->getActualCameraIndex(), -1);
}

TEST(CameraReader_setSource, WhenTryToSetAnAvailableValue_ShouldSetActualCameraIndex){
  auto sut = new CameraReader();

  EXPECT_EQ(sut->getActualCameraIndex(), -1);

  sut->setSource("0");
  EXPECT_EQ(sut->getActualCameraIndex(), 0);
}

TEST(CameraReader_setBrightness, WhenTryToSetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setBrightness(50));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}

TEST(CameraReader_getBrightness, WhenTryToGetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_EQ(sut->getBrightness(), 0);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}

TEST(CameraReader_setGain, WhenTryToSetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setGain(50));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}

TEST(CameraReader_getGain, WhenTryToGetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_EQ(sut->getGain(), 0);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}


TEST(CameraReader_setSaturation, WhenTryToSetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setSaturation(50));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}

TEST(CameraReader_getSaturation, WhenTryToGetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_EQ(sut->getSaturation(), 0);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}


TEST(CameraReader_setContrast, WhenTryToSetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_NO_THROW(sut->setContrast(50));
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
}

TEST(CameraReader_getContrast, WhenTryToGetValueWithCaptureClosed_ShouldCerrAnError){
  auto sut = new CameraReader();

  testing::internal::CaptureStderr();
  EXPECT_EQ(sut->getContrast(), 0);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_STREQ("[Error] capture is closed\n", output.c_str());
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