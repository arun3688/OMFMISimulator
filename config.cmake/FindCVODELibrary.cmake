# Update this to have more specific rules for finding the cvode library.

find_library(CVODELibrary_LIBRARY
  NAMES sundials_cvode
  HINTS ${CVODELibrary_ROOT}/lib
)

if(CVODELibrary_LIBRARY)
  message(STATUS "Found CVODELibrary")
  message(STATUS "  " ${CVODELibrary_LIBRARY})
  set(CVODELibrary_LIBRARYDIR ${CVODELibrary_ROOT}/lib)
  set(CVODELibrary_INCLUDEDIR ${CVODELibrary_ROOT}/include)
else()
  if(CVODELibrary_FIND_REQUIRED)
    message(STATUS "Unable to find the requested CVODELibrary" )
    message(STATUS "Looked in CVODELibrary_ROOT ${CVODELibrary_ROOT}" )
    message(SEND_ERROR "Could not find cvode. Make sure you have set the CVODELibrary_ROOT in the CMakeFile.txt to point to your CVODELibrary installation." )
  else()
    message(STATUS "CVODELibrary - NOT Found" )
  endif(CVODELibrary_FIND_REQUIRED)
endif()
