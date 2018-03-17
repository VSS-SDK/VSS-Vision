//
// Created by johnathan on 16/03/18.
//

#include "gtest/gtest.h"
#include "CameraReader.h"

TEST(CameraReader, ConstructionShouldHaveRightParameters){
  auto cameraReader = new CameraReader();
  EXPECT_EQ(cameraReader->getRunningCapture(), false);
  EXPECT_EQ(cameraReader->getCamerasIndex().size(), 1);
  EXPECT_EQ(cameraReader->getShouldCloseReader(), false);
  EXPECT_EQ(cameraReader->getActualCameraIndex(), -1);
  EXPECT_EQ(cameraReader->getActualFrame().cols, 0);
  EXPECT_EQ(cameraReader->getActualFrame().rows, 0);
  EXPECT_EQ(cameraReader->getCapture().isOpened(), false);
}
