//
// Created by johnathan on 17/03/18.
//

#include <include/gtest/gtest.h>
#include <ColorRecognizer.h>

TEST(ColorRecognizer_setColorRange, WhenSetColorRange_ShouldChangeValue){
  auto sut = new ColorRecognizer();

  EXPECT_EQ(sut->getColorRange().colorType, ColorType::UnknownType);

  float min[3] = {20, 20, 20};
  float max[3] = {50, 50, 50};
  sut->setColorRange(new ColorRange(ColorType::Blue, min, max));

  EXPECT_EQ(sut->getColorRange().colorType, ColorType::Blue);
}

