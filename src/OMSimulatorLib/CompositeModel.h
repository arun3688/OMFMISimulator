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

#ifndef _OMS_MODEL_H_
#define _OMS_MODEL_H_

#include "FMUWrapper.h"
#include "DirectedGraph.h"
#include "Settings.h"
#include "Types.h"

#include <fmilib.h>
#include <string>
#include <map>
#include <deque>

class CompositeModel
{
public:
  CompositeModel();
  CompositeModel(const std::string& descriptionPath);
  ~CompositeModel();

  void instantiateFMU(const std::string& filename, const std::string& instanceName);
  void setReal(const std::string& var, double value);
  double getReal(const std::string& var);
  void addConnection(const std::string& from, const std::string& to);
  void exportDependencyGraph(const std::string& prefix);

  void describe();
  void simulate();

  oms_status_t doSteps(const int numberOfSteps);
  oms_status_t stepUntil(const double timeValue);

  void initialize();
  void terminate();

  oms_status_t getCurrentTime(double *time);

  Settings& getSettings() {return settings;}

private:
  void updateInputs(DirectedGraph& graph);

private:
  Settings settings;
  std::map<std::string, FMUWrapper*> fmuInstances;
  DirectedGraph outputsGraph;
  DirectedGraph initialUnknownsGraph;
  double tcur;
  oms_modelState_t modelState;
};

#endif
