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

TEST(CameraReader_setSource, WhenTryToSendANotANumValue_ShouldNotSetActualCameraIndex){
  auto sut = new CameraReader();
  EXPECT_NO_THROW(sut->setSource("NAN - Not a Num"));
  EXPECT_EQ(sut->getActualCameraIndex(), -1);
  // TODO: Test cerr << "message" << endl;
}