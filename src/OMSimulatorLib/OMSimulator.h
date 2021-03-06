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

#ifndef _OMSIMULATOR_H_
#define _OMSIMULATOR_H_

#include "Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief Creates an empty composite model.
 *
 * @return model instance as opaque pointer.
 */
void* oms_newModel();

/**
 * \brief Loads a composite model from xml representation.
 *
 * @param filename Full path to the composite model xml representation.
 * @return model instance as opaque pointer.
 */
void* oms_loadModel(const char* filename);

// TODO saveModel

/**
 * \brief Unloads a composite model.
 *
 * @param model Model as opaque pointer.
 */
void oms_unload(void* model);

/**
 * \brief Instantiates a FMU.
 *
 * @param model Model as opaque pointer.
 * @param filename Full path to the FMU.
 * @param instanceName Instance name for further access.
 */
void oms_instantiateFMU(void* model, const char* filename, const char* instanceName);

/**
 * \brief Set real parameter value.
 *
 * @param model Model as opaque pointer.
 * @param var
 * @param value
 */
void oms_setReal(void *model, const char *var, double value);
// TODO: setInteger
// TODO: setBoolean
// TODO: setString

/**
 * \brief Get real value.
 *
 * @param model Model as opaque pointer.
 * @param var
 * @return value
 */
double oms_getReal(void *model, const char *var);
// TODO: getInteger
// TODO: getBoolean
// TODO: getString

/**
 * \brief Add a connection from a FMU output to a FMU input.
 *
 * @param model Model as opaque pointer.
 * @param from Name of an FMU output.
 * @param to Name of an FMU input.
 */
void oms_addConnection(void* model, const char* from, const char* to);


void oms_simulate(void* model);

/**
 * \brief In case of variable step sizes or events we cannot know the final time value.
 *
 * @param model Model as opaque pointer.
 * @param numberOfSteps Number of steps.
 * @return Error status.
 */
oms_status_t oms_doSteps(const void* model, const int numberOfSteps);

/**
 * \brief Performs a sub-simulation run from the current time instance to a given time value
 *
 * @param model Model as opaque pointer.
 * @param timeValue
 * @return Error status.
 */
oms_status_t oms_stepUntil(const void* model, const double timeValue);

void oms_describe(void* model);
void oms_exportDependencyGraph(void* model, const char* filename);

/**
 * \brief Initialize the simulation of a given model.
 *
 * @param model Model as opaque pointer.
 * @return Error status.
 */
oms_status_t oms_initialize(void* model);

/**
 * \brief Terminate the simulation of a given model.
 *
 * @param model Model as opaque pointer.
 * @return Error status.
 */
oms_status_t oms_terminate(void* model);

/**
 * \brief Get current simulation time.
 *
 * @param model [in]  Model as opaque pointer.
 * @param time  [out] Minimal time value that is reached by all instances.
 * @return Error status.
 */
oms_status_t oms_getCurrentTime(const void* model, double* time);

void oms_setStartTime(void* model, double startTime);
void oms_setStopTime(void* model, double stopTime);
void oms_setTolerance(void* model, double tolerance);
void oms_setWorkingDirectory(void* model, const char* filename);
void oms_setResultFile(void* model, const char* filename);

/**
 * \brief Returns the library's version string.
 *
 * @return version string
 */
const char* oms_getVersion();

#ifdef __cplusplus
}
#endif

#endif
