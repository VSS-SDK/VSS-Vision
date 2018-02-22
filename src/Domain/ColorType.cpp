//
// Created by johnathan on 20/02/18.
//

#include <Domain/ColorType.h>

std::string toDescription(ColorType colorType) {
  switch (colorType){
    case ColorType::Brown:
      return "Brown";
    case ColorType::Purple:
      return "Purple";
    case ColorType::Pink:
      return "Pink";
    case ColorType::Green:
      return "Green";
    case ColorType::Orange:
      return "Orange";
    case ColorType::Yellow:
      return "Yellow";
    case ColorType::Blue:
      return "Blue";
    case ColorType::Red:
      return "Red";
    default:
      return "Unknown";
  }
}

ColorType toColorType(std::string colorName) {
  if(colorName == "Brown")
    return ColorType::Brown;

  if(colorName == "Purple")
    return ColorType::Purple;

  if(colorName == "Pink")
    return ColorType::Pink;

  if(colorName == "Green")
    return ColorType::Green;

  if(colorName == "Orange")
    return ColorType::Orange;

  if(colorName == "Yellow")
    return ColorType::Yellow;

  if(colorName == "Blue")
    return ColorType::Blue;

  if(colorName == "Red")
    return ColorType::Red;

  return ColorType::UnknownType;
}
