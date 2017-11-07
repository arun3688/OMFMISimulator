project(OMSimulatorPython)

set(CMAKE_INSTALL_RPATH "$ORIGIN")


include_directories(${PYTHON_INCLUDE_DIRS} ../OMSimulatorLib)

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${FMILibrary_LIBRARYDIR})
link_directories(${CVODELibrary_LIBRARYDIR})
link_directories(${KINSOLLibrary_LIBRARYDIR})

# Shared library version
add_library(OMSimulatorPython SHARED OMSimulatorPython.c)
IF (WIN32 OR APPLE)
  target_link_libraries(OMSimulatorPython OMSimulatorLib_shared fmilib_shared sundials_kinsol sundials_cvode sundials_nvecserial ${PYTHON_LIBRARIES})
ELSE ()
  target_link_libraries(OMSimulatorPython OMSimulatorLib_shared fmilib_shared sundials_kinsol sundials_cvode sundials_nvecserial ${PYTHON_LIBRARIES})
ENDIF ()

install(TARGETS OMSimulatorPython DESTINATION lib)
