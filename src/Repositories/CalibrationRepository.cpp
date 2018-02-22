/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Core/StringHelper.h>
#include "CalibrationRepository.h"

Calibration CalibrationRepository::read(std::string pathName){
  std::ifstream ifs (pathName, std::ifstream::in);
  Calibration *calibration = new Calibration();

  for (std::string line; std::getline(ifs, line); )
  {
    auto colorType = hasColorType(line);
    if(colorType != ColorType::UnknownType) {
      setCalibrationColorRange(*calibration, ifs, colorType);
    }

    auto configurationType = hasConfigurationType(line);
    if(configurationType != ConfigurationType::UnknownConfiguration){
      setCalibrationConfiguration(*calibration, ifs, configurationType);
    }

    auto cutType = hasCutType(line);
    if(cutType != CutType::UnknownCut){
      setCalibrationCut(*calibration, ifs);
    }
  }

  return calibration;
}

void CalibrationRepository::create(std::string pathName, Calibration calibration){
  if(calibration.colorsRange.size() < 7 && calibration.cut.size() < 2)
    return;

  std::ofstream file;
  file.open (pathName);

  file << "# Rotation" << std::endl;
  file << calibration.rotation << std::endl;
  file << std::endl;

  file << "# Brightness" << std::endl;
  file << calibration.brightness << std::endl;
  file << std::endl;

  file << "# Contrast" << std::endl;
  file << calibration.contrast << std::endl;
  file << std::endl;

  file << "# Saturation" << std::endl;
  file << calibration.saturation << std::endl;
  file << std::endl;

  file << "# Exposure" << std::endl;
  file << calibration.exposure << std::endl;
  file << std::endl;

  file << "# Gain" << std::endl;
  file << calibration.gain << std::endl;
  file << std::endl;

  file << "# Cuts" << std::endl;
  for(unsigned int i = 0 ; i < calibration.cut.size() ; i++)
    file << calibration.cut.at(i).x << " " << calibration.cut.at(i).y << std::endl;
  file << std::endl;

  file << "# Blue" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[0].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[0].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Yellow" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[1].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[1].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Orange" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[2].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[2].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Green" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[3].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[3].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Pink" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[4].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[4].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Purple" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[5].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[5].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Red" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[6].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[6].max[i] << " ";
  file << std::endl;
  file << std::endl;

  file << "# Brown" << std::endl;
  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[7].min[i] << " ";
  file << std::endl;

  for(int i = 0 ; i < 3 ; i++)
    file << calibration.colorsRange[7].max[i] << " ";

  file.close();
}

Calibration CalibrationRepository::update(std::string pathName, Calibration calibration){
  // TODO
  return new Calibration();
}

void CalibrationRepository::remove(std::string pathName){
  // TODO
}

void CalibrationRepository::setCalibrationConfiguration(Calibration &calibration, std::ifstream &file,
                                                        ConfigurationType &configurationType) {
  std::string line;
  std::getline(file, line);

  switch(configurationType){
    case ConfigurationType::Rotation:
      calibration.rotation = stof(line);
      break;
    case ConfigurationType::Gain:
      calibration.gain = stof(line);
      break;
    case ConfigurationType::Exposure:
      calibration.exposure = stof(line);
      break;
    case ConfigurationType::Saturation:
      calibration.saturation = stof(line);
      break;
    case ConfigurationType::Contrast:
      calibration.contrast = stof(line);
      break;
    case ConfigurationType::Brightness:
      calibration.brightness = stof(line);
      break;
    case ConfigurationType::UnknownConfiguration:
      break;
  }
}

void CalibrationRepository::setCalibrationCut(Calibration &calibration, std::ifstream &file) {
  std::string line;

  std::getline(file, line);
  auto cutValuesBottom = explode(line, ' ');
  calibration.cut.push_back(new Point2d(stof(cutValuesBottom.at(0)), stof(cutValuesBottom.at(1))));

  std::getline(file, line);
  auto cutValuesTop = explode(line, ' ');
  calibration.cut.push_back(new Point2d(stof(cutValuesTop.at(0)), stof(cutValuesTop.at(1))));
}

void CalibrationRepository::setCalibrationColorRange(Calibration &calibration, std::ifstream &file, ColorType &colorType) {
  auto colorRange = new ColorRange();
  std::string line;

  colorRange->colorType = colorType;

  std::getline(file, line);
  auto minValues = explode(line, ' ');

  for(unsigned int i = 0 ; i < minValues.size() || i < 3; i++)
    colorRange->min[i] = stof(minValues.at(i));

  std::getline(file, line);
  auto maxValues = explode(line, ' ');

  for(unsigned int i = 0 ; i < maxValues.size() || i < 3; i++)
    colorRange->max[i] = stof(maxValues.at(i));

  calibration.colorsRange.push_back(colorRange);
}

// TODO: arrumar um jeito de melhorar essa verificação
CutType CalibrationRepository::hasCutType(std::string name) {
  if(name == "# Cuts")
    return CutType::DefaultCut;

  return CutType::UnknownCut;
}

// TODO: arrumar um jeito de melhorar essa verificação
ColorType CalibrationRepository::hasColorType(std::string name){
  if(name == "# Blue")
    return ColorType::Blue;

  if(name == "# Yellow")
    return ColorType::Yellow;

  if(name == "# Orange")
    return ColorType::Orange;

  if(name == "# Red")
    return ColorType::Red;

  if(name == "# Green")
    return ColorType::Green;

  if(name == "# Pink")
    return ColorType::Pink;

  if(name == "# Purple")
    return ColorType::Purple;

  if(name == "# Brown")
    return ColorType::Brown;

  return ColorType::UnknownType;
}

// TODO: arrumar um jeito de melhorar essa verificação
ConfigurationType CalibrationRepository::hasConfigurationType(std::string name){
  if(name == "# Rotation")
    return ConfigurationType::Rotation;

  if(name == "# Brightness")
    return ConfigurationType::Brightness;

  if(name == "# Contrast")
    return ConfigurationType::Contrast;

  if(name == "# Saturation")
    return ConfigurationType::Saturation;

  if(name == "# Exposure")
    return ConfigurationType::Exposure;

  if(name == "# Gain")
    return ConfigurationType::Gain;

  return ConfigurationType::UnknownConfiguration;
}
