MESSAGE( STATUS "External project - Eigen" )

SET( Eigen_VERSION "3.3.3" )

ExternalProject_Add( Eigen
  PREFIX Eigen
  URL "http://bitbucket.org/eigen/eigen/get/${Eigen_VERSION}.tar.gz"
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

SET(Eigen_DIR "${CMAKE_BINARY_DIR}/Eigen/src/Eigen")
MESSAGE(STATUS "Eigen is here : ${Eigen_DIR}" )

