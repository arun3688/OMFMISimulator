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

#ifndef _OMS_SETTINGS_H_
#define _OMS_SETTINGS_H_

class Settings
{
public:
  Settings();
  ~Settings();

  void SetStartTime(double startTime);
  double* GetStartTime();
  void ClearStartTime();

  void SetStopTime(double stopTime);
  double* GetStopTime();
  void ClearStopTime();

  void SetTolerance(double tolerance);
  double* GetTolerance();
  void ClearTolerance();

  void SetTempDirectory(const char* tempDir);
  const char* GetTempDirectory();
  void ClearTempDirectory();

  void SetResultFile(const char* resultFile);
  const char* GetResultFile();
  void ClearResultFile();

private:
  // stop the compiler generating methods of copy the object
  Settings(Settings const& copy);            // not implemented
  Settings& operator=(Settings const& copy); // not implemented

  double* startTime;
  double* stopTime;
  double* tolerance;
  char* tempDir;
  char* resultFile;
};

#endif
