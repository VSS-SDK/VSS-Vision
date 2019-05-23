//
// Created by johnathan on 27/02/18.
//

#include <Domain/Calibration.h>
#include <Builders/CalibrationBuilder.h>

CalibrationBuilder::CalibrationBuilder() {
  haveToInitializeColors = false;
  haveToInitializeCuts = false;
}

void CalibrationBuilder::shouldInitializeColors(bool haveToInitializeColors) {
  this->haveToInitializeColors = haveToInitializeColors;
}

void CalibrationBuilder::shouldInitializeCuts(bool haveToInitializeCuts) {
  this->haveToInitializeCuts = haveToInitializeCuts;
}

Calibration CalibrationBuilder::getInstance() {
  auto calibration = new Calibration();

  if(haveToInitializeColors)
    calibration->colorsRange = getColorsRange();

  if(haveToInitializeCuts)
    calibration->cut = getCuts();

  return calibration;
}

std::vector<ColorRange> CalibrationBuilder::getColorsRange() {
  std::vector<ColorRange> colorsRange;

  auto colorRangeAux = new ColorRange();

  colorRangeAux->colorType = ColorType::Blue;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Yellow;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Orange;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Green;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Pink;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Purple;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Red;
  colorsRange.emplace_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Brown;
  colorsRange.emplace_back(colorRangeAux);

  return colorsRange;
}

std::vector<vss::Point> CalibrationBuilder::getCuts() {
  std::vector<vss::Point> cuts;

  cuts.push_back(vss::Point(0,0));
  cuts.push_back(vss::Point(0,0));
  cuts.push_back(vss::Point(0,0));
  cuts.push_back(vss::Point(0,0));

  return cuts;
}

bool CalibrationBuilder::getHaveToInitializeColors() {
  return haveToInitializeColors;
}

bool CalibrationBuilder::getHaveToInitializeCuts() {
  return haveToInitializeCuts;
}
