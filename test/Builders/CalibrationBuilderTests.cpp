//
// Created by johnathan on 17/03/18.
//


#include "gtest/gtest.h"
#include "Builders/CalibrationBuilder.h"

TEST(CalibrationBuilder_Constructor, WhenBuildObject_ShouldHaveRightParametersValue){
  auto sut = new CalibrationBuilder();

  EXPECT_FALSE(sut->getHaveToInitializeColors());
  EXPECT_FALSE(sut->getHaveToInitializeCuts());
}

TEST(CalibrationBuilder_getCuts, WhenGetCutsShouldReturnAVectorWithTwoElements){
  auto sut = new CalibrationBuilder();
  auto cuts = sut->getCuts();

  EXPECT_EQ(cuts.size(), 2);

  for(unsigned int i = 0 ; i < cuts.size() ; i++){
    EXPECT_EQ(cuts.at(i).x, 0);
    EXPECT_EQ(cuts.at(i).y, 0);
  }
}

TEST(CalibrationBuilder_getColorsRange, WhenGetColorsRangeShouldReturnAVectorWithEightElements){
  auto sut = new CalibrationBuilder();
  auto colorsRange = sut->getColorsRange();

  EXPECT_EQ(colorsRange.size(), 8);

  for(unsigned int i = 0 ; i < colorsRange.size() ; i++){
    for(unsigned int j = 0 ; j < 3 ; j++) {
      EXPECT_EQ(colorsRange.at(i).min[j], 0);
      EXPECT_EQ(colorsRange.at(i).max[j], 0);
    }
  }

  EXPECT_EQ(colorsRange.at(0).colorType, ColorType::Red);
  EXPECT_EQ(colorsRange.at(1).colorType, ColorType::Yellow);
  EXPECT_EQ(colorsRange.at(2).colorType, ColorType::Orange);
  EXPECT_EQ(colorsRange.at(3).colorType, ColorType::Green);
  EXPECT_EQ(colorsRange.at(4).colorType, ColorType::Pink);
  EXPECT_EQ(colorsRange.at(5).colorType, ColorType::Purple);
  EXPECT_EQ(colorsRange.at(6).colorType, ColorType::Brown);
  EXPECT_EQ(colorsRange.at(7).colorType, ColorType::Blue);
}

TEST(CalibrationBuilder_shouldInitializeColors, WhenCallShouldInitializeColors_ShouldSetToTrue){
  auto sut = new CalibrationBuilder();

  EXPECT_FALSE(sut->getHaveToInitializeColors());

  sut->shouldInitializeColors(true);
  EXPECT_TRUE(sut->getHaveToInitializeColors());
}

TEST(CalibrationBuilder_shouldInitializeCuts, WhenCallShouldInitializeCuts_ShouldSetToTrue){
  auto sut = new CalibrationBuilder();

  EXPECT_FALSE(sut->getHaveToInitializeCuts());

  sut->shouldInitializeCuts(true);
  EXPECT_TRUE(sut->getHaveToInitializeCuts());
}

TEST(CalibrationBuilder_getInstance, WhenGetInstanceWithoutAnySet_ShouldReturnObjectWithoutAnyVectors){
  auto sut = new CalibrationBuilder();
  auto calibration = sut->getInstance();

  EXPECT_EQ(calibration.colorsRange.size(), 0);
  EXPECT_EQ(calibration.cut.size(), 0);
}

TEST(CalibrationBuilder_getInstance, WhenGetInstanceWithSetCuts_ShouldReturnObjectWithCuts){
  auto sut = new CalibrationBuilder();
  sut->shouldInitializeCuts(true);
  auto calibration = sut->getInstance();

  EXPECT_EQ(calibration.colorsRange.size(), 0);
  EXPECT_NE(calibration.cut.size(), 0);
}

TEST(CalibrationBuilder_getInstance, WhenGetInstanceWithSetColors_ShouldReturnObjectWithColors){
  auto sut = new CalibrationBuilder();
  sut->shouldInitializeColors(true);
  auto calibration = sut->getInstance();

  EXPECT_NE(calibration.colorsRange.size(), 0);
  EXPECT_EQ(calibration.cut.size(), 0);
}

TEST(CalibrationBuilder_getInstance, WhenGetInstanceWithSetColorsAndSetCuts_ShouldReturnObjectWithColorsAndCuts){
  auto sut = new CalibrationBuilder();
  sut->shouldInitializeColors(true);
  sut->shouldInitializeCuts(true);
  auto calibration = sut->getInstance();

  EXPECT_NE(calibration.colorsRange.size(), 0);
  EXPECT_NE(calibration.cut.size(), 0);
}