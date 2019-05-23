//
// Created by johnathan on 17/03/18.
//

#include <gtest/gtest.h>
#include <Repositories/CalibrationRepository.h>
#include <Builders/CalibrationBuilder.h>

TEST(CalibrationRepository_Constructor, WhenBuildObject_ShouldHaveRightParametersValue){
  auto sut = new CalibrationRepository(new CalibrationBuilder());

  EXPECT_NE(sut->getCalibrationBuilder(), nullptr);
}

TEST(CalibrationRepository_hasCutType, WhenStringDoestHaveAValidValue_ShouldReturnUnknown){
  auto sut = new CalibrationRepository(new CalibrationBuilder());

  EXPECT_EQ(sut->hasCutType("# Not Cuts"), CutType::UnknownCut);
}

TEST(CalibrationRepository_hasCutType, WhenStringHasAValidValue_ShouldReturnDefault){
  auto sut = new CalibrationRepository(new CalibrationBuilder());

  EXPECT_EQ(sut->hasCutType("# Cuts"), CutType::DefaultCut);
}

TEST(CalibrationRepository_hasColorType, WhenStringDoestHaveAValidValue_ShouldReturnUnknown){
  auto sut = new CalibrationRepository(new CalibrationBuilder());

  EXPECT_EQ(sut->hasCutType("# Not Color"), CutType::UnknownCut);
}

TEST(CalibrationRepository_hasColorType, WhenStringHasAValidValue_ShouldReturnDefault){
  auto sut = new CalibrationRepository(new CalibrationBuilder());

  EXPECT_EQ(sut->hasColorType("# Blue"), ColorType::Blue);
  EXPECT_EQ(sut->hasColorType("# Yellow"), ColorType::Yellow);
  EXPECT_EQ(sut->hasColorType("# Orange"), ColorType::Orange);
  EXPECT_EQ(sut->hasColorType("# Red"), ColorType::Red);
  EXPECT_EQ(sut->hasColorType("# Green"), ColorType::Green);
  EXPECT_EQ(sut->hasColorType("# Pink"), ColorType::Pink);
  EXPECT_EQ(sut->hasColorType("# Purple"), ColorType::Purple);
  EXPECT_EQ(sut->hasColorType("# Brown"), ColorType::Brown);
}