cmake_minimum_required(VERSION 2.8)
project(OMSimulator)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/config.cmake/")
include(GetGitRevisionDescription)
git_describe(GIT_VERSION_STRING --tags --abbrev=7 --match=v*.*)

#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_BUILD_TYPE DEBUG)

# Don't allow in-source build
IF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "No in-source builds supported. Change to 'build' sub-directory and do 'cmake ..'.")
ENDIF()

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install CACHE PATH "Library installation path (don't change)" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

##########################
# Configuring for boost "FindBoost.cmake"
IF (WIN32)
  set(BOOST_ROOT "C:/local/boost_1_63_0")
ENDIF()
# BTH FIXME I would prefer to link against static, but Ubuntu 14.04 ships static boost libraries which are compiled without -fPIC and thus cannot be linked into the OMSimulator shared library. Is it Possible to use static versions for linking against executables, but shared versions for linking against shared libraries?
# set(Boost_USE_STATIC_LIBS ON)
# BTH There is more what can be set. What do we want?
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
# Boost v1.54 is the boost shipped with my Ubuntu 14.04, lower versions may work, too.
find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
IF (Boost_FOUND)
  message("-- Boost settings")
  message("--   Include path: ${Boost_INCLUDE_DIRS}")
  message("--   Library path: ${Boost_LIBRARY_DIRS}")
  message("--   Libraries: ${Boost_LIBRARIES}")
ELSE()
	MESSAGE(WARNING, "Boost library not found, please give a hint by setting the cmake variable BOOST_ROOT either in the cmake-gui or the command line, e.g., 'cmake -DBOOST_ROOT=C:/local/boost_1_63_0'")
ENDIF()

# Set where your FMILibrary is installed here
IF (WIN32)
  set(FMILibrary_ROOT ${PROJECT_SOURCE_DIR}/3rdParty/FMIL/install/win)
ELSE()
  set(FMILibrary_ROOT ${PROJECT_SOURCE_DIR}/3rdParty/FMIL/install/linux)
ENDIF()
find_package(FMILibrary REQUIRED)

IF (WIN32)
  set(LUALibrary_ROOT ${PROJECT_SOURCE_DIR}/3rdParty/Lua/install/win)
ELSE()
  set(LUALibrary_ROOT ${PROJECT_SOURCE_DIR}/3rdParty/Lua/install/linux)
ENDIF()
find_package(LUALibrary REQUIRED)

##########################
# Add project modules
add_subdirectory(src/OMSimulatorLib)
add_subdirectory(src/OMSimulator)
add_subdirectory(src/OMSimulatorLua)

##########################
# TODO Add tests
