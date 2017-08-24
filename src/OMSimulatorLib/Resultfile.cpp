/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

#include "Resultfile.h"
#include "Logging.h"
#include "Util.h"
#include "Settings.h"
#include "FMUWrapper.h"
#include <fmilib.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

// https://stackoverflow.com/a/3418285
void replaceAll(std::string& str, const std::string& from, const std::string& to)
{
  if (from.empty())
    return;

  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
}

Resultfile::Resultfile(std::string filename)
{

}

Resultfile::~Resultfile()
{
  resultFile.close();
  logDebug("Result file closed");
}

void Resultfile::emitresultvariables()
{
  resultFile.open(resultfilename.c_str());
  resultFile << "time";
  for (int j=0; j<resultvariables.size(); j++)
  {
      resultFile << ", " << resultvariables[j].getFMUInstanceName() << "." << resultvariables[j].getName();
  }
  resultFile << std::endl;
}

void Resultfile::emitresultvalues(double time)
{
  resultFile << time;
  for (int j=0; j<resultvariables.size(); j++)
  {
     FMUWrapper* fmuinstance= resultvariables[j].getFMUInstance();
     switch (resultvariables[j].getBaseType())
      {
        case fmi2_base_type_real:
          resultFile << ", " << fmuinstance->getReal(resultvariables[j].getName());
          break;
        // case fmi2_base_type_int:
        // case fmi2_base_type_bool:
        // case fmi2_base_type_str:
        // case fmi2_base_type_enum:
        default:
          logWarning("Resultfile::emitresultvalues: unsupported base type");
      }
  }
  resultFile << std::endl;
}