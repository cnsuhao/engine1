cmake_minimum_required(VERSION 3.2)

project(BioGears)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

## Pull and Compile dependencies
set (Pull_Dependencies false CACHE BOOL "Initial pull and build of all dependent libraries/executables")
if(Pull_Dependencies)
  include(cmake/ExternalDependencies.cmake)
elseif(NOT Pull_Dependencies)
  include(cmake/BioGears.cmake)
endif()