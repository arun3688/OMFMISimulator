#include <OMSimulator.h>

#ifdef _WIN32
  #define DLLEXPORT __declspec(dllexport)
#else
  #define DLLEXPORT
#endif

DLLEXPORT void * newModel()
{
  oms_newModel();
}

DLLEXPORT void * loadModel(const char* filename)
{
  oms_loadModel(filename);
}

DLLEXPORT void  instantiateFMU(void* model, const char* filename, const char* instanceName)
{
  oms_instantiateFMU(model, filename, instanceName);
}

DLLEXPORT void instantiateTable(void* model, const char* filename, const char* instanceName)
{
  oms_instantiateTable(model, filename, instanceName);
}

DLLEXPORT void * describe(void* model)
{
  oms_describe(model);
}

DLLEXPORT void addConnection(void* model, const char* from, const char* to)
{
  oms_addConnection(model,from,to);
}

DLLEXPORT void importXML(void* model, const char* filename)
{
  oms_importXML(model, filename);
}

DLLEXPORT void exportXML(void* model, const char* filename)
{
  oms_exportXML(model, filename);
}

DLLEXPORT void exportDependencyGraph(void* model, const char* filename)
{
  oms_exportDependencyGraph(model, filename);
}

DLLEXPORT void exportCompositeStructure(void* model, const char* filename)
{
  oms_exportCompositeStructure(model, filename);
}

DLLEXPORT oms_status_t getCurrentTime(const void* model)
{
  double time;
  oms_getCurrentTime(model, &time);
  return time;
}

DLLEXPORT oms_status_t reset(void* model)
{
  oms_reset(model);
}

DLLEXPORT oms_status_t simulate(void* model)
{
  oms_simulate(model);
}

DLLEXPORT oms_status_t initialize(void* model)
{
  oms_initialize(model);
}

DLLEXPORT oms_status_t terminate(void* model)
{
  oms_terminate(model);
}

DLLEXPORT oms_status_t unload(void* model)
{
  oms_unload(model);
}

DLLEXPORT oms_status_t doSteps(const void* model, const int numberOfSteps)
{
  oms_doSteps(model, numberOfSteps);
}

DLLEXPORT oms_status_t stepUntil(const void* model, const double timeValue)
{
  oms_stepUntil(model, timeValue);
}

DLLEXPORT const char* getVersion()
{
  oms_getVersion();
}

DLLEXPORT int getBoolean(void *model, const char *var)
{
  oms_getBoolean(model,var);
}

DLLEXPORT int getInteger(void *model, const char *var)
{
  oms_getInteger(model,var);
}

DLLEXPORT double getReal(void *model, const char *var)
{
  oms_getReal(model,var);
}

DLLEXPORT void setBoolean(void *model, const char *var, int value)
{
  oms_setBoolean(model,var,value);
}

DLLEXPORT void setInteger(void *model, const char *var, int value)
{
  oms_setInteger(model,var,value);
}

DLLEXPORT void setReal(void *model, const char *var, double value)
{
  oms_setReal(model,var,value);
}

DLLEXPORT void setResultFile(void* model, const char* filename)
{
  oms_setResultFile(model,filename);
}

DLLEXPORT void setTempDirectory(const char* filename)
{
  oms_setTempDirectory(filename);
}

DLLEXPORT void setWorkingDirectory(const char* path)
{
  oms_setWorkingDirectory(path);
}

DLLEXPORT void setStartTime(void* model, double startTime)
{
  oms_setStartTime(model, startTime);
}

DLLEXPORT void setStopTime(void* model, double stopTime)
{
  oms_setStopTime(model, stopTime);
}

DLLEXPORT void setTolerance(void* model, double tolerance)
{
  oms_setTolerance(model,tolerance);
}

DLLEXPORT void setCommunicationInterval(void* model, double CommunicationInterval)
{
  oms_setCommunicationInterval(model,CommunicationInterval);
}

DLLEXPORT void setSolverMethod(void* model, const char* instanceName, const char* method)
{
  oms_setSolverMethod(model,instanceName,method);
}

DLLEXPORT void setLogFile(const char* filename)
{
  oms_setLogFile(filename);
}

DLLEXPORT int compareSimulationResults(const char* filenameA, const char* filenameB, const char* var, double relTol, double absTol)
{
  oms_compareSimulationResults(filenameA,filenameB,var,relTol,absTol);
}

DLLEXPORT void setVariableFilter(void* model, const char* instanceFilter, const char* variableFilter)
{
  oms_setVariableFilter(model,instanceFilter,variableFilter);
}

DLLEXPORT int getNumberOfInterfaces(void *model)
{
  oms_getNumberOfInterfaces(model);
}

DLLEXPORT oms_causality_t getInterfaceCausality(void *model, int idx)
{
  oms_getInterfaceCausality(model,idx);
}

DLLEXPORT const char *getInterfaceName(void *model, int idx)
{
  oms_getInterfaceName(model,idx);
}

DLLEXPORT const char *getInterfaceVariable(void *model, int idx)
{
  oms_getInterfaceVariable(model,idx);
}
