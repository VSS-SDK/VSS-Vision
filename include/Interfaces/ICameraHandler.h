/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include ICAMERA_READER_H
#define ICAMERA_READER_H

// Vai servir para buscar os dados do opencv
// Vai ser utilizado tanto na calibragem quanto na fase de execução
// Calibragem e execucao vai implementar essa interface
// Não poderá ser utilizado a calibragem e a execução ao mesmo tempo
// Quando for trocar entre um e outro, utilizar dynamic_cast
class ICameraReader{

};

#endif // ICAMERA_READER_H