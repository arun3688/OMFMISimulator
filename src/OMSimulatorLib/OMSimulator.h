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
 * \brief Set real value.
 *
 * @param model Model as opaque pointer.
 * @param var
 * @param value
 */
void oms_setReal(void *model, const char *var, double value);
// TODO: setInteger
// TODO: setBoolean
// TODO: setString

// TODO: getReal
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
void oms_describe(void* model);
void oms_exportDependencyGraph(void* model, const char* filename);

void oms_setStartTime(double startTime);
void oms_setStopTime(double stopTime);
void oms_setTolerance(double tolerance);
void oms_setWorkingDirectory(const char* filename);
void oms_setResultFile(const char* filename);

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