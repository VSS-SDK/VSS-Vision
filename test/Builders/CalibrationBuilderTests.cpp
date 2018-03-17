//
// Created by johnathan on 17/03/18.
//


#include "gtest/gtest.h"
#include "Builders/CalibrationBuilder.h"

TEST(CalibrationBuilder_Constructor, WhenBuildObject_ShouldHaveRightParametersValue){
  auto sut = new CalibrationBuilder();
  EXPECT_EQ(sut->getHaveToInitializeColors(), false);
  EXPECT_EQ(sut->getHaveToInitializeCuts(), false);
}
