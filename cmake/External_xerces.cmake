MESSAGE( STATUS "External project - XERCES" )

SET( xerces_VERSION "3.1.4" )

		
SET(xerces_DIR "${CMAKE_BINARY_DIR}/xerces/src/xerces/")
ExternalProject_Add( xerces
  PREFIX xerces
  URL "https://github.com/rleigh-codelibre/xerces-c/archive/cmake-trunk.zip"
  UPDATE_COMMAND 
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND ""
)

SET(xerces_DIR "${CMAKE_BINARY_DIR}/xerces/src/xerces")
MESSAGE(STATUS "xerces is here : ${xerces_DIR}" )
