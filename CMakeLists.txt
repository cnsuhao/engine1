cmake_minimum_required(VERSION 3.2)

project(BioGears_SuperBuild)

set (SUPERBUILD ON CACHE BOOL "Initial pull and build of all dependent libraries/executables")
if(SUPERBUILD)
  include(cmake/ExternalDependencies.cmake)
else()
  include(BioGears.cmake)
endif()