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

add_custom_target(UpdateVerification ALL)
add_dependencies(UpdateVerification ExternalData)
add_custom_command(TARGET UpdateVerification POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory   ${CMAKE_INSTALL_PREFIX}/bin/verification)
add_custom_command(TARGET UpdateVerification POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/verification/verification.zip 
            WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/verification
)