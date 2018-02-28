//
// Created by johnathan on 27/02/18.
//

#include <Domain/Calibration.h>
#include <Factories/CalibrationFactory.h>

Calibration CalibrationFactory::createCalibrationWithoutColors() {
  auto calibration = new Calibration();

  calibration->cut.push_back(new Point2d(0.0, 0.0));
  calibration->cut.push_back(new Point2d(0.0, 0.0));

  return calibration;
}

Calibration CalibrationFactory::createCalibrationWithoutCuts() {
  auto calibration = new Calibration();

  auto colorRangeAux = new ColorRange();

  colorRangeAux->colorType = ColorType::Red;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Yellow;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Orange;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Green;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Pink;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Purple;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Brown;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Blue;
  calibration->colorsRange.push_back(colorRangeAux);

  return calibration;
}

Calibration CalibrationFactory::createCalibrationWithoutColorsAndCuts() {
  return new Calibration();
}

Calibration CalibrationFactory::createCalibrationWithColorsAndCuts() {
  auto calibration = new Calibration();

  auto colorRangeAux = new ColorRange();

  colorRangeAux->colorType = ColorType::Red;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Yellow;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Orange;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Green;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Pink;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Purple;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Brown;
  calibration->colorsRange.push_back(colorRangeAux);

  colorRangeAux->colorType = ColorType::Blue;
  calibration->colorsRange.push_back(colorRangeAux);

  calibration->cut.push_back(new Point2d(0.0, 0.0));
  calibration->cut.push_back(new Point2d(0.0, 0.0));

  return calibration;
}

void CalibrationFactory::shouldInitializeColors(bool) {

}

void CalibrationFactory::shouldInitializeCuts(bool) {

}

Calibration CalibrationFactory::getInstance() {
  return Calibration();
}
