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
#include <fmilib.h>
#include "CompositeModel.h"
#include "Variable.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <tuple>

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

Resultfile::Resultfile(std::string filename, CompositeModel* model, std::string test)
{
  this->model = model;

  result.open(filename.c_str());
  logDebug("Result file: " + filename);

  result << "time";
  std::cout << "inside Result file" << std::endl;
  std::map<std::string, FMUWrapper*>::iterator it;
  std::cout << "inside Result file1" << std::endl;
  for (it=model->getFMUInstances().begin(); it != model->getFMUInstances().end(); it++)
  {
    std::vector<Variable> allVariables = it->second->getAllVariables();
    for (int i=0; i<allVariables.size(); i++)
      //if (fmi2_base_type_real == allVariables[i].baseType) // TODO: support other base types as well
     // std::string value= allVariables[i].getvarname();
      result << ", " << it->first+"."+allVariables[i].getvarname();
      //std::cout <<"inside loop" << value << std::endl;
      //std::cout << "inside for loop" << it->first<< allVariables[i].getvarname() << std::endl;
  }
  result << std::endl;
}

Resultfile::~Resultfile()
{
  resultFile.close();
  logDebug("Result file closed");
}

void Resultfile::emitarun()
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
          std::string value = toString(it->second->getReal(allVariables[i].getvarname()));
          result << ", " << it->second->getReal(allVariables[i].getvarname());
         }
  }
  result << std::endl;

}


void Resultfile::emitnew(double time, std::string instancename)
{
  //double time1;
  //model->getCurrentTime(&time1);
  std::cout << "inside emit_new " << time << std::endl;
  //result << time;

  std::map<std::string, FMUWrapper*>::iterator it;
  std::vector<std::string> vals;
  for (it=model->getFMUInstances().begin(); it != model->getFMUInstances().end(); it++)
  {
    if (it->first == instancename)
     {
       std::vector<Variable> allVariables = it->second->getAllVariables();
       for (int i=0; i<allVariables.size(); i++)
         {
          std::string value = toString(it->second->getReal(allVariables[i].getvarname()));
          vals.push_back(value);
          //result << ", " << it->second->getReal(allVariables[i].getvarname());
         }
    }
  }
  //mapdata[time]=vals;
  //mapdata.insert ( std::pair<double,>('z',500) );
  /*
  for(std::string n : vals) {
        std::cout <<"arunnew" << time << "=" << n << std::endl;
    }
   */
  //std::cout << "check new value system" <<
}

void Resultfile::emit(double time)
{
  std::cout << "inside emit " << time << std::endl;
  resultFile << time;
  std::vector<std::string> val;
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
    //data.emplace_back(time,value);
    val.push_back(value);
    resultFile << ", " << value;
  }
  /*
  for(std::string n : val) {
        std::cout <<"arun" << time << "=" << n << std::endl;
    }*/
  //mapdata[time]=val;
  resultFile << std::endl;
}

void Resultfile::emitvalue()
{
  std::cout << "inside emitvalue" << std::endl;

  std::map<double,std::vector<std::string>> ::iterator param;
  for (param=mapdata.begin(); param!=mapdata.end(); ++param)
  {
     std::cout <<"arun" << "=" << param->first << std::endl;
     //result << param->first;
     std::vector<std::string> vallist = param->second;
     for(std::string n : vallist)
     {
        std::cout <<"roger" << n << std::endl;
        //result << ", " << n;
     }
  //result << std::endl;
  }
}