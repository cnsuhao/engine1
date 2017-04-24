MESSAGE( STATUS "External project - XSD" )

SET( xsd_VERSION "4.0.0" )

IF(MSVC)
  SET( xsd_URL "http://www.codesynthesis.com/download/xsd/4.0/windows/i686/xsd-4.0.0-i686-windows.zip")
ELSEIF(APPLE)
  SET( xsd_URL "http://www.codesynthesis.com/download/xsd/4.0/macosx/i686/xsd-4.0.0-i686-macosx.tar.bz2")
ELSEIF(UNIX)
  SET( xsd_URL "http://www.codesynthesis.com/download/xsd/4.0/linux-gnu/x86_64/xsd-4.0.0-x86_64-linux-gnu.tar.bz2")
ENDIF()
		
SET(xsd_DIR "${CMAKE_BINARY_DIR}/xsd/src/xsd/")		
ExternalProject_Add( xsd
  PREFIX xsd
  URL ${xsd_URL}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

SET(xsd_DIR "${CMAKE_BINARY_DIR}/xsd/src/xsd")
MESSAGE(STATUS "xsd is here : ${xsd_DIR}" )
