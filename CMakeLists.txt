cmake_minimum_required(VERSION 3.2)

project(BioGears_SuperBuild)

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set (SUPERBUILD ON CACHE BOOL "Initial pull and build of all dependent libraries/executables")
if(SUPERBUILD)
  include(cmake/ExternalDependencies.cmake)
else()
  include(BioGears.cmake)
endif()
