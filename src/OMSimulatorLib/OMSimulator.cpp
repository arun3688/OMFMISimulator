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

#include "OMSimulator.h"
#include "CompositeModel.h"
#include "Logging.h"
#include "Settings.h"
#include "Version.h"
#include "Types.h"

void* oms_newModel()
{
  logTrace();
  CompositeModel* pModel = new CompositeModel();
  return (void*) pModel;
}

void* oms_loadModel(const char* filename)
{
  logTrace();
  CompositeModel* pModel = new CompositeModel(filename);
  return (void*) pModel;
}

void oms_unload(void* model)
{
  logTrace();
  if(!model)
  {
    logError("oms_unload: invalid pointer");
    return;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  delete pModel;
}

void oms_instantiateFMU(void* model, const char* filename, const char* instanceName)
{
  logTrace();
  if(!model)
  {
    logError("oms_instantiateFMU: invalid pointer");
    return;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->instantiateFMU(filename, instanceName);
}

void oms_setReal(void *model, const char *var, double value)
{
  logTrace();
  if (!model)
  {
    logError("oms_setReal: invalid pointer");
    return;
  }

  CompositeModel *pModel = (CompositeModel *)model;
  pModel->setReal(var, value);
}

double oms_getReal(void *model, const char *var)
{
  logTrace();
  if (!model)
  {
    // TODO: Provide suitable return value to handle unsuccessful calls.
    logFatal("oms_getReal: invalid pointer");
  }

  CompositeModel *pModel = (CompositeModel *)model;
  return pModel->getReal(var);
}

void oms_addConnection(void* model, const char* from, const char* to)
{
  logTrace();
  if(!model)
  {
    logError("oms_addConnection: invalid pointer");
    return;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->addConnection(from, to);
}

void oms_simulate(void* model)
{
  logTrace();
  if(!model)
  {
    logError("oms_simulate: invalid pointer");
    return;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->simulate();
}

oms_status_t oms_doSteps(const void* model, const int numberOfSteps)
{
  logTrace();
  if(!model)
  {
    logError("oms_doSteps: invalid pointer");
    return oms_status_error;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  return pModel->doSteps(numberOfSteps);
}

oms_status_t oms_stepUntil(const void* model, const double timeValue)
{
  logTrace();
  if(!model)
  {
    logError("oms_stepUntil: invalid pointer");
    return oms_status_error;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  return pModel->stepUntil(timeValue);
}

void oms_describe(void* model)
{
  logTrace();
  if(!model)
  {
    logError("oms_describe: invalid pointer");
    return;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->describe();
}

void oms_exportDependencyGraph(void* model, const char* filename)
{
  logTrace();
  if(!model)
  {
    logError("oms_exportDependencyGraph: invalid pointer");
    return;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->exportDependencyGraph(filename);
}

oms_status_t oms_initialize(void* model)
{
  logTrace();
  if(!model)
  {
    logError("oms_initialize: invalid pointer");
    return oms_status_error;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->initialize();
  return oms_status_ok;
}

oms_status_t oms_terminate(void* model)
{
  logTrace();
  if(!model)
  {
    logError("oms_terminate: invalid pointer");
    return oms_status_error;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  pModel->terminate();
  return oms_status_ok;
}

oms_status_t oms_getCurrentTime(const void* model, double* time)
{
  logTrace();
  if(!model)
  {
    logError("oms_getCurrentTime: invalid pointer");
    return oms_status_error;
  }

  CompositeModel* pModel = (CompositeModel*) model;
  return pModel->getCurrentTime(time);
}

void oms_setStartTime(void* model, double startTime)
{
  logTrace();
  CompositeModel* pModel = (CompositeModel*) model;
  pModel->getSettings().SetStartTime(startTime);
}

void oms_setStopTime(void* model, double stopTime)
{
  logTrace();
  CompositeModel* pModel = (CompositeModel*) model;
  pModel->getSettings().SetStopTime(stopTime);
}

void oms_setTolerance(void* model, double tolerance)
{
  logTrace();
  CompositeModel* pModel = (CompositeModel*) model;
  pModel->getSettings().SetTolerance(tolerance);
}

void oms_setWorkingDirectory(void* model, const char* filename)
{
  logTrace();
  CompositeModel* pModel = (CompositeModel*) model;
  pModel->getSettings().SetTempDirectory(filename);
}

void oms_setResultFile(void* model, const char* filename)
{
  logTrace();
  CompositeModel* pModel = (CompositeModel*) model;
  pModel->getSettings().SetResultFile(filename);
}

const char* oms_getVersion()
{
  return oms_git_version;
}
