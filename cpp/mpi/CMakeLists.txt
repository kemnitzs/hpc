CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(boost_mpi_test)

SET( CMAKE_BUILD_TYPE RELEASE )
option( USE_ADDRESS_SANITIZER "use address sanitizer of gcc/clang" OFF )
option( USE_LIBRARY_ACCESS_CHECK "use std++ build in access detection for containers" OFF )
option( USE_BACKWARD "use backward cpp" ON )

# packages to use remember to load openmpi/2.1.1 and boost/1.69.0
FIND_PACKAGE( Boost COMPONENTS mpi serialization REQUIRED )
FIND_PACKAGE( MPI REQUIRED )

# subdirectories to use
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backward_cpp)

# compiler flags
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native" )
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic" )
if ( ${USE_ADDRESS_SANITIZER} )
  SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address" )
endif()
if ( ${USE_LIBRARY_ACCESS_CHECK} )
  SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG" )
endif()
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" )

SET( CMAKE_CXX_STANDARD 14 )
SET( CMAKE_EXPORT_COMPILE_COMMANDS on )

# the executable 
ADD_EXECUTABLE(bin_boost_mpi_test main.cpp ${BACKWARD_ENABLE})

if ( ${USE_BACKWARD} )
  add_backward(bin_boost_mpi_test)
endif()

TARGET_INCLUDE_DIRECTORIES( bin_boost_mpi_test PRIVATE ${Boost_INCLUDE_DIRS} ${MPI_INCLUDE_PATH})
TARGET_LINK_LIBRARIES( bin_boost_mpi_test ${Boost_LIBRARIES} ${MPI_LIBRARIES})
