# External Data
include(ExternalData)
set(ExternalData_URL_TEMPLATES "https://data.kitware.com/api/v1/file/hashsum/%(algo)/%(hash)/download")
ExternalData_Add_Test(ExternalData
  NAME Download
  COMMAND 
  DATA{verification.zip}
  )
ExternalData_Add_Target(ExternalData)
set(ExternalData_LINK_CONTENT SHA512)
set(ExternalData_TIMEOUT_ABSOLUTE 0)

set(INC_DOWNLOAD)
if(DOWNLOAD_BASELINES)
  set(INC_DOWNLOAD ALL)
else()
  set_target_properties(ExternalData PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
endif()

add_custom_target(UpdateVerification ${INC_DOWNLOAD})
add_dependencies(UpdateVerification ExternalData)
add_custom_command(TARGET UpdateVerification POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory   ${CMAKE_INSTALL_PREFIX}/bin/verification)
add_custom_command(TARGET UpdateVerification POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/verification/verification.zip 
            WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/verification
)