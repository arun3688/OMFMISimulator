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

#ifndef _OMS_DIRECTEDGRAPH_H_
#define _OMS_DIRECTEDGRAPH_H_

#include "Variable.h"

#include <fmilib.h>
#include <string>
#include <vector>
#include <map>
#include <deque>

class DirectedGraph
{
public:
  DirectedGraph();
  ~DirectedGraph();

  int addVariable(const Variable& var);
  void addEdge(const Variable& var1, const Variable& var2);

  void dotExport(const std::string& filename);

  void includeGraph(const DirectedGraph& graph);

  const std::vector< std::pair<int, int> >& getSortedConnections();
  std::vector<Variable> nodes;
  std::vector< std::pair<int, int> > edges;

private:
  std::deque< std::vector<int> > getSCCs();
  void calculateSortedConnections();

private:
  std::vector< std::vector<int> > G;
  std::vector< std::pair<int, int> > sortedConnections;
  bool sortedConnectionsAreValid;
};

#endif
