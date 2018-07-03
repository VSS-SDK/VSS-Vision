//
// Created by johnathan on 17/03/18.
//

#include <include/gtest/gtest.h>
#include <ColorRecognizerTwoColors.h>

TEST(ColorRecognizerTwoColors_setColorRange, WhenSetColorRange_ShouldChangeValue){
  auto sut = new ColorRecognizerTwoColors();

  EXPECT_EQ(sut->getColorRange().colorType, ColorType::Unknown);

  float min[3] = {20, 20, 20};
  float max[3] = {50, 50, 50};
  sut->setColorRange(new ColorRange(ColorType::Blue, min, max));

  EXPECT_EQ(sut->getColorRange().colorType, ColorType::Blue);
}

TEST(ColorRecognizerTwoColors_getCenter, WhenGetCenter_ShouldGetRightCenter){
  auto sut = new ColorRecognizerTwoColors();
  auto center = sut->getCenter(cv::Rect(cv::Point(0,0), cv::Point(10, 10)));

  EXPECT_EQ(center, cv::Point2f(5,5));
}
