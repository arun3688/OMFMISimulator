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

#include "CompositeModel.h"
#include "Logging.h"
#include "DirectedGraph.h"
#include "Settings.h"
#include "Types.h"

#include <fmilib.h>
#include <JM/jm_portability.h>

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <deque>

#include <boost/filesystem.hpp>

CompositeModel::CompositeModel()
  : fmuInstances()
{
  logTrace();
  modelState = oms_modelState_instantiated;
}

CompositeModel::CompositeModel(const std::string& descriptionPath)
{
  logTrace();
  logError("Function not implemented yet: CompositeModel::CompositeModel");
  modelState = oms_modelState_instantiated;
}

CompositeModel::~CompositeModel()
{
  logTrace();
  std::map<std::string, FMUWrapper*>::iterator it;
  for (it=fmuInstances.begin(); it != fmuInstances.end(); it++)
    delete it->second;
}

void CompositeModel::instantiateFMU(const std::string& filename, const std::string& instanceName)
{
  logTrace();
  fmuInstances[instanceName] = new FMUWrapper(*this, filename, instanceName);
  outputsGraph.includeGraph(fmuInstances[instanceName]->getOutputsGraph());
  initialUnknownsGraph.includeGraph(fmuInstances[instanceName]->getInitialUnknownsGraph());
}

void CompositeModel::setReal(const std::string& var, double value)
{
  logTrace();
  std::stringstream var_(var);
  std::string fmuInstance;
  std::string fmuVar;

  // TODO: Improve this
  std::getline(var_, fmuInstance, '.');
  std::getline(var_, fmuVar);

  if (fmuInstances.find(fmuInstance) == fmuInstances.end())
  {
    logError("CompositeModel::setReal: FMU instance \"" + fmuInstance + "\" doesn't exist in model");
    return;
  }

  fmuInstances[fmuInstance]->setRealParameter(fmuVar, value);
}

double CompositeModel::getReal(const std::string& var)
{
  logTrace();
  std::stringstream var_(var);
  std::string fmuInstance;
  std::string fmuVar;

  // TODO: Improve this
  std::getline(var_, fmuInstance, '.');
  std::getline(var_, fmuVar);

  if (fmuInstances.find(fmuInstance) == fmuInstances.end())
  {
    // TODO: Provide suitable return value to handle unsuccessful calls.
    logFatal("CompositeModel::getReal: FMU instance \"" + fmuInstance + "\" doesn't exist in model");
  }

  return fmuInstances[fmuInstance]->getReal(fmuVar);
}

void CompositeModel::addConnection(const std::string& from, const std::string& to)
{
  logTrace();
  std::stringstream var1_(from);
  std::stringstream var2_(to);
  std::string fmuInstance1, fmuInstance2;
  std::string fmuVar1, fmuVar2;

  // TODO: Improve this
  std::getline(var1_, fmuInstance1, '.');
  std::getline(var1_, fmuVar1);

  // TODO: Improve this
  std::getline(var2_, fmuInstance2, '.');
  std::getline(var2_, fmuVar2);

  if (fmuInstances.find(fmuInstance1) == fmuInstances.end())
  {
    logError("CompositeModel::addConnection: FMU instance \"" + fmuInstance1 + "\" doesn't exist in model");
    return;
  }

  if (fmuInstances.find(fmuInstance2) == fmuInstances.end())
  {
    logError("CompositeModel::addConnection: FMU instance \"" + fmuInstance2 + "\" doesn't exist in model");
    return;
  }

  Variable *var1 = fmuInstances[fmuInstance1]->getVariable(fmuVar1);
  Variable *var2 = fmuInstances[fmuInstance2]->getVariable(fmuVar2);

  outputsGraph.addEdge(*var1, *var2);
  initialUnknownsGraph.addEdge(*var1, *var2);
}

void CompositeModel::exportDependencyGraph(const std::string& prefix)
{
  logTrace();
  initialUnknownsGraph.dotExport(prefix + "_initialization.dot");
  outputsGraph.dotExport(prefix + "_simulation.dot");
}

void CompositeModel::describe()
{
  logTrace();

  std::map<std::string, FMUWrapper*>::iterator it;

  std::cout << "# FMU instances" << std::endl;
  for (it=fmuInstances.begin(); it != fmuInstances.end(); it++)
  {
    std::cout << it->first << std::endl;
    std::cout << "  - " << it->second->getFMUKind() << std::endl;
    std::cout << "  - path: " << it->second->getFMUPath() << std::endl;
    std::cout << "  - GUID: " << it->second->getGUID() << std::endl;
    std::cout << "  - tool: " << it->second->getGenerationTool() << std::endl;

    std::cout << "  - input interface:" << std::endl;
    DirectedGraph graph = it->second->getOutputsGraph();
    for (int j=0; j<graph.nodes.size(); j++)
      if (graph.nodes[j].isInput())
        std::cout << "    - input " << graph.nodes[j].name << std::endl;

    std::cout << "  - output interface:" << std::endl;
    for (int j=0; j<graph.nodes.size(); j++)
      if (graph.nodes[j].isOutput())
        std::cout << "    - output " << graph.nodes[j].name << std::endl;
  }

  //std::cout << "\n# Parameters" << std::endl;
  //std::cout << "TODO" << std::endl;

  std::cout << "\n# Simulation settings" << std::endl;
  std::cout << "  - start time: " << settings.GetStartTime() << std::endl;
  std::cout << "  - stop time: " << settings.GetStopTime() << std::endl;
  std::cout << "  - tolerance: " << settings.GetTolerance() << std::endl;
  std::cout << "  - result file: " << (settings.GetResultFile() ? settings.GetResultFile() : "<no result file>") << std::endl;
  //std::cout << "  - temp directory: " << settings.GetTempDirectory() << std::endl;

  std::cout << "\n# Composite structure" << std::endl;
  std::cout << "## Initialization" << std::endl;
  // calculate sorting
  const std::vector< std::pair<int, int> >& connectionsInitialUnknowns = initialUnknownsGraph.getSortedConnections();
  for(int i=0; i<connectionsInitialUnknowns.size(); i++)
  {
    int output = connectionsInitialUnknowns[i].first;
    int input = connectionsInitialUnknowns[i].second;
    std::string outputFMU = initialUnknownsGraph.nodes[output].fmuInstance;
    std::string outputVar = initialUnknownsGraph.nodes[output].name;
    std::string inputFMU = initialUnknownsGraph.nodes[input].fmuInstance;
    std::string inputVar = initialUnknownsGraph.nodes[input].name;
    std::cout << outputFMU << "." << outputVar << " -> " << inputFMU << "." << inputVar << std::endl;
  }

  std::cout << "\n## Simulation" << std::endl;
  // calculate sorting
  const std::vector< std::pair<int, int> >& connectionsOutputs = outputsGraph.getSortedConnections();
  for(int i=0; i<connectionsOutputs.size(); i++)
  {
    int output = connectionsOutputs[i].first;
    int input = connectionsOutputs[i].second;
    std::string outputFMU = outputsGraph.nodes[output].fmuInstance;
    std::string outputVar = outputsGraph.nodes[output].name;
    std::string inputFMU = outputsGraph.nodes[input].fmuInstance;
    std::string inputVar = outputsGraph.nodes[input].name;
    std::cout << outputFMU << "." << outputVar << " -> " << inputFMU << "." << inputVar << std::endl;
  }

  std::cout << std::endl;
}

void CompositeModel::updateInputs(DirectedGraph& graph)
{
  const std::vector< std::pair<int, int> >& sortedConnections = graph.getSortedConnections();

  // input = output
  for(int i=0; i<sortedConnections.size(); i++)
  {
    int output = sortedConnections[i].first;
    int input = sortedConnections[i].second;
    std::string& outputFMU = graph.nodes[output].fmuInstance;
    std::string& outputVar = graph.nodes[output].name;
    std::string& inputFMU = graph.nodes[input].fmuInstance;
    std::string& inputVar = graph.nodes[input].name;
    double value = fmuInstances[outputFMU]->getReal(outputVar);
    fmuInstances[inputFMU]->setReal(inputVar, value);
    //std::cout << inputFMU << "." << inputVar << " = " << outputFMU << "." << outputVar << std::endl;
  }
}

void CompositeModel::simulate()
{
  logTrace();

  initialize();

  double* pStopTime = settings.GetStopTime();
  fmi2_real_t tend = pStopTime ? *pStopTime : 1.0;
  stepUntil(tend);

  terminate();
}

oms_status_t CompositeModel::doSteps(const int numberOfSteps)
{
  logTrace();

  if (oms_modelState_simulation != modelState)
  {
    logError("CompositeModel::doSteps: Model is not in simulation mode.");
    return oms_status_error;
  }

  double hdef = 1e-1;
  for(int step=0; step<numberOfSteps; step++)
  {
    // input = output
    updateInputs(outputsGraph);

    // do_step
    std::map<std::string, FMUWrapper*>::iterator it;
    for (it=fmuInstances.begin(); it != fmuInstances.end(); it++)
      it->second->doStep(tcur);
    tcur += hdef;
  }

  return oms_status_ok;
}

oms_status_t CompositeModel::stepUntil(const double timeValue)
{
  logTrace();

  if (oms_modelState_simulation != modelState)
  {
    logError("CompositeModel::stepUntil: Model is not in simulation mode.");
    return oms_status_error;
  }

  while(tcur < timeValue)
  {
    doSteps(1);
  }

  return oms_status_ok;
}

void CompositeModel::initialize()
{
  logTrace();

  if (oms_modelState_instantiated != modelState)
  {
    logFatal("CompositeModel::initialize: Model is already in simulation mode.");
  }

  double* pStartTime = settings.GetStartTime();
  tcur = pStartTime ? *pStartTime : 0.0;

  // Enter initialization
  modelState = oms_modelState_initialization;
  std::map<std::string, FMUWrapper*>::iterator it;
  for (it=fmuInstances.begin(); it != fmuInstances.end(); it++)
    it->second->enterInitialization(tcur);

  updateInputs(initialUnknownsGraph);

  // Exit initialization
  for (it=fmuInstances.begin(); it != fmuInstances.end(); it++)
    it->second->exitInitialization();
  modelState = oms_modelState_simulation;
}

void CompositeModel::terminate()
{
  logTrace();

  if (oms_modelState_initialization != modelState &&
      oms_modelState_simulation != modelState)
  {
    logInfo("CompositeModel::terminate: No simulation to terminate.");
    return;
  }

  std::map<std::string, FMUWrapper*>::iterator it;
  for (it=fmuInstances.begin(); it != fmuInstances.end(); it++)
    it->second->terminate();

  modelState = oms_modelState_instantiated;
}

oms_status_t CompositeModel::getCurrentTime(double *time)
{
  logTrace();

  if (oms_modelState_initialization != modelState &&
      oms_modelState_simulation != modelState)
  {
    logError("It is only allowed to call 'getCurrentTime' while running a simulation.");
    return oms_status_error;
  }

  *time = tcur;
  return oms_status_ok;
}

