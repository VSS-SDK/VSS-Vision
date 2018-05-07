//
// Created by johnathan on 16/03/18.
//

#include "gtest/gtest.h"
#include "Core/StringHelper.h"

TEST(explode, WhenReceiveContentWithRightDelimiter_ShouldReturnTheRightNumberOfContents){
  EXPECT_EQ(2, explode("Teste1#Teste2", '#').size());
  EXPECT_EQ(3, explode("Teste1#Teste2#Teste3", '#').size());
}

TEST(explode, WhenReceiveContentWithWrongDelimiter_ShouldReturnOneElement){
  EXPECT_EQ(1, explode("Teste1#Teste2#Teste3", '-').size());
}

TEST(explode, WhenReceiveContentWithEmptyCharAfterDelimiter_ShouldReturnTwoElements){
  EXPECT_EQ(1, explode("Teste1#", '#').size());
}

TEST(explode, WhenReceiveEmptyContent_ShouldReturnZeroElements){
  EXPECT_EQ(0, explode("", '-').size());
}
