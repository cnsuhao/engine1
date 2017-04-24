MESSAGE( STATUS "External project - Log4cpp" )

SET( log4cpp_VERSION "1.1.2" )
		
SET(log4cpp_DIR "${CMAKE_BINARY_DIR}/log4cpp/src/log4cpp/")		
ExternalProject_Add( log4cpp
  PREFIX log4cpp
  URL "https://sourceforge.net/projects/log4cpp/files/log4cpp-1.1.x%20%28new%29/log4cpp-1.1/log4cpp-1.1.2.tar.gz"
  UPDATE_COMMAND 
#    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/cmake/log4cpp.cmake" "${log4cpp_DIR}/CMakeLists.txt"
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${log4cpp_DIR}-build/bin
#  CMAKE_ARGS -Dlog4cpp_DIR:PATH=${log4cpp_DIR}
  BUILD_IN_SOURCE 1
    
  INSTALL_COMMAND ""
)

MESSAGE(STATUS "log4cpp is here : ${log4cpp_DIR}" )
