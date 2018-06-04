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

  calibration->shouldCropImage = false;

  return calibration;
}

std::vector<ColorRange> CalibrationBuilder::getColorsRange() {
  std::vector<ColorRange> colorsRange;

  auto colorRangeAux = new ColorRange();

  colorRangeAux->colorType = ColorType::Red;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Yellow;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Orange;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Green;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Pink;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Purple;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Brown;
  colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Blue;
  colorsRange.push_back(colorRangeAux);

  return colorsRange;
}

std::vector<Point2d> CalibrationBuilder::getCuts() {
  std::vector<Point2d> cuts;

  cuts.push_back(Point2d(0,0));
  cuts.push_back(Point2d(0,0));

  return cuts;
}

bool CalibrationBuilder::getHaveToInitializeColors() {
  return haveToInitializeColors;
}

bool CalibrationBuilder::getHaveToInitializeCuts() {
  return haveToInitializeCuts;
}
