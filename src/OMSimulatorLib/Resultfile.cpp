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
#include "Variable.h"
#include "CompositeModel.h"
#include <fmilib.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

Resultfile::Resultfile(std::string filename, fmi2_import_t* fmu)
{
  this->fmu = fmu;
  resultFile.open(filename.c_str());
  logDebug("Result file: " + filename);

  resultFile << "time";

  fmi2_import_variable_list_t *list = fmi2_import_get_variable_list(fmu, 0);
  size_t nVar = fmi2_import_get_variable_list_size(list);
  for (size_t i = 0; i < nVar; ++i)
  {
    fmi2_import_variable_t* var = fmi2_import_get_variable(list, i);
    std::string name = fmi2_import_get_variable_name(var);
    resultFile << ", " << name;
  }

  resultFile << std::endl;
}

Resultfile::Resultfile(std::string filename, CompositeModel* model)
{
  this->model = model;
  result.open(filename.c_str());
  logDebug("Result file: " + filename);
  result << "time";
  std::map<std::string, FMUWrapper*>::iterator it;
  for (it=model->getFMUInstances().begin(); it != model->getFMUInstances().end(); it++)
  {
    std::vector<Variable> allVariables = it->second->getAllVariables();
    for (int i=0; i<allVariables.size(); i++)
    {
        result << ", " << it->first << "." << allVariables[i].getName();
    }
  }
  result << std::endl;
}

Resultfile::~Resultfile()
{
  resultFile.close();
  result.close();
  logDebug("Result file closed");
}

void Resultfile::emit(double time)
{
  resultFile << time;

  fmi2_import_variable_list_t *list = fmi2_import_get_variable_list(fmu, 0);
  size_t nVar = fmi2_import_get_variable_list_size(list);
  for (size_t i = 0; i < nVar; ++i)
  {
    fmi2_import_variable_t* var = fmi2_import_get_variable(list, i);
    std::string value = "???";

    if (fmi2_base_type_real == fmi2_import_get_variable_base_type(var))
    {
      double real_value;
      fmi2_value_reference_t vr = fmi2_import_get_variable_vr(var);
      fmi2_import_get_real(fmu, &vr, 1, &real_value);
      value = toString(real_value);
    }
    else if (fmi2_base_type_int == fmi2_import_get_variable_base_type(var))
    {
      int int_value;
      fmi2_value_reference_t vr = fmi2_import_get_variable_vr(var);
      fmi2_import_get_integer(fmu, &vr, 1, &int_value);
      value = toString(int_value);
    }
    else if (fmi2_base_type_bool == fmi2_import_get_variable_base_type(var))
    {
      int bool_value;
      fmi2_value_reference_t vr = fmi2_import_get_variable_vr(var);
      fmi2_import_get_boolean(fmu, &vr, 1, &bool_value);
      value = bool_value ? "1" : "0";
    }
    // TODO: string
    else
      logWarning("Resultfile::emit: unsupported base type");

    resultFile << ", " << value;
  }

  resultFile << std::endl;
}

void Resultfile::emitnew()
{
  double time;
  model->getCurrentTime(&time);
  result << time;
  std::map<std::string, FMUWrapper*>::iterator it;
  for (it=model->getFMUInstances().begin(); it != model->getFMUInstances().end(); it++)
  {
    std::vector<Variable> allVariables = it->second->getAllVariables();
    for (int i=0; i<allVariables.size(); i++)
    {
      switch (allVariables[i].getBaseType())
      {
        case fmi2_base_type_real:
          result << ", " << it->second->getReal(allVariables[i].getName());
          break;
        // case fmi2_base_type_int:
        // case fmi2_base_type_bool:
        // case fmi2_base_type_str:
        // case fmi2_base_type_enum:
        default:
          logWarning("Resultfile::emitnew: unsupported base type");
      }
    }
  }
  result << std::endl;
}
