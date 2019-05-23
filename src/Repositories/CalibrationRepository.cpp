/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Helpers/StringHelper.h>
#include "CalibrationRepository.h"

Calibration CalibrationRepository::read(std::string pathName){
    std::ifstream ifs (pathName, std::ifstream::in);

    auto calibration = calibrationBuilder->getInstance();

    for (std::string line; std::getline(ifs, line); )
    {
        auto colorType = hasColorType(line);
        if(colorType != ColorType::UnknownType) {
            setCalibrationColorRange(calibration, ifs, colorType);
        }

        auto cutType = hasCutType(line);
        if(cutType != CutType::UnknownCut){
            setCalibrationCut(calibration, ifs);
        }
    }
    return calibration;
}

void CalibrationRepository::create(std::string pathName, Calibration calibration){
    if(calibration.colorsRange.size() < 7 && calibration.cut.size() < 2){
        std::cout << "colors " << calibration.colorsRange.size() << std::endl;
        std::cout << "cuts " << calibration.cut.size() << std::endl;
        return;
    }

    std::ofstream file;
    file.open (pathName);

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
    file << std::endl;
    file << std::endl;

    file << "# Cuts" << std::endl;
    for(unsigned int i = 0 ; i < calibration.cut.size() ; i++)
        file << calibration.cut.at(i).x << " " << calibration.cut.at(i).y << std::endl;
    file << std::endl;

    file.close();
}

void CalibrationRepository::setCalibrationCut(Calibration &calibration, std::ifstream &file) {
    std::string line;

    std::getline(file, line);
    auto cutValues1 = explode(line, ' ');
    calibration.cut.emplace_back(vss::Point(stof(cutValues1.at(0)), stof(cutValues1.at(1))));

    std::getline(file, line);
    auto cutValues2 = explode(line, ' ');
    calibration.cut.emplace_back(vss::Point(stof(cutValues2.at(0)), stof(cutValues2.at(1))));

    std::getline(file, line);
    auto cutValues3 = explode(line, ' ');
    calibration.cut.emplace_back(vss::Point(stof(cutValues3.at(0)), stof(cutValues3.at(1))));

    std::getline(file, line);
    auto cutValues4 = explode(line, ' ');
    calibration.cut.emplace_back(vss::Point(stof(cutValues4.at(0)), stof(cutValues4.at(1))));
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

    calibration.colorsRange.emplace_back(colorRange);
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

CalibrationRepository::CalibrationRepository(ICalibrationBuilder *calibrationBuilder) {
    this->calibrationBuilder = calibrationBuilder;
    calibrationBuilder->shouldInitializeColors(false);
    calibrationBuilder->shouldInitializeCuts(false);
}

ICalibrationBuilder *CalibrationRepository::getCalibrationBuilder() {
    return calibrationBuilder;
}
