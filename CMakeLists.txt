cmake_minimum_required ( VERSION 3.6.0 )
project ( LSMLibrary )

option( BUILD_UNIT_TESTS OFF "Build unit tests for the LSM library" )

# project dirs
set( SRC_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src     )
set( INC_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( CUDA_DIR ${SRC_DIR}/cuda                     )


#
# Project configuration file
#


# compile flags
list(
     APPEND INTENSE_FLAGS
     -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy
     -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations
     -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual
     -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -fPIC
     -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
     )

#
# compile main cpp library
#
set( PROJECT_LIB_NAME lsm )

add_library(
            ${PROJECT_LIB_NAME}

            ${INC_DIR}/lsm/SparseMatrix.hpp
            # ${INC_DIR}/lsm/MatrixMultiply.hpp

            ${SRC_DIR}/SparseMatrix.cpp
            # ${SRC_DIR}/MatrixMultiply.cpp
            )

target_include_directories( ${PROJECT_LIB_NAME} PUBLIC ${INC_DIR} ${SRC_DIR} )

set_property( TARGET ${PROJECT_LIB_NAME} PROPERTY CXX_STANDARD 14          )
set_property( TARGET ${PROJECT_LIB_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )

if ( NOT MSVC )
  set_target_properties( ${PROJECT_LIB_NAME} PROPERTIES COMPILE_FLAGS ${INTENSE_FLAGS} )
endif( )


####################
#       CUDA       #
####################
find_package( CUDA )

if ( CUDA_FOUND )

  include_directories( ${INC_DIR} ${SRC_DIR} ${SRC_DIR}/gpu )

  # set nvcc options
  if( UNIX OR APPLE )
    list( APPEND CUDA_NVCC_FLAGS
         -Xcompiler -fPIC -O3 --compiler-options -fno-strict-aliasing -use_fast_math )
  endif( )

  if( APPLE )
    list( APPEND CUDA_NVCC_FLAGS -Xcompiler -Wno-unused-function)
  endif( )

  # Auto detect compute architecture
  if ( NOT CUDA_ARCH_FLAGS )
    cuda_select_nvcc_arch_flags( CUDA_ARCH_FLAGS Auto )
    set( CUDA_ARCH_FLAGS ${CUDA_ARCH_FLAGS} CACHE STRING "gencode architecture flags for nvcc" )
  endif( )

  list( APPEND CUDA_NVCC_FLAGS ${CUDA_ARCH_FLAGS} --std=c++11 --expt-relaxed-constexpr )


  set( CUDA_LIB gpu${PROJECT_NAME} )

  # build CUDA library
  cuda_add_library(
                   ${CUDA_LIB}

                   ${INC_DIR}/lsm/gpu/SparseMatrixGpu.hpp

                   ${SRC_DIR}/gpu/SparseMatrixGpu.cu
                   )

  set_property( TARGET ${CUDA_LIB} PROPERTY CXX_STANDARD 14          )
  set_property( TARGET ${CUDA_LIB} PROPERTY CXX_STANDARD_REQUIRED ON )

  if ( NOT MSVC )
    set_target_properties( ${CUDA_LIB} PROPERTIES COMPILE_FLAGS ${INTENSE_FLAGS} )
  endif( )

  target_link_libraries( ${PROJECT_LIB_NAME} ${CUDA_LIB} )
  add_dependencies     ( ${PROJECT_LIB_NAME} ${CUDA_LIB} )

endif( CUDA_FOUND )





###########################
#       Google Test       #
###########################

if ( BUILD_UNIT_TESTS )

  include( cmake/DownloadProject.cmake )

  # Download and unpack googletest at configure time
  DownloadProject( cmake/CMakeLists.txt.googletest googletest )

  # Prevent overriding the parent project's compiler/linker settings on Windows
  set( gtest_force_THIRDPARTY_crt ON CACHE BOOL "" FORCE )

  # Add googlemock directly to the project build
  add_subdirectory( ${CMAKE_BINARY_DIR}/googletest-src/googlemock
                    ${CMAKE_BINARY_DIR}/googletest-build )

  # Build unit tests executable
  set( UNIT_TESTS_EXEC test${PROJECT_NAME} )

  add_executable(
                 ${UNIT_TESTS_EXEC}

                 ${SRC_DIR}/testing/TemplateUnitTests.cpp
                 )

  target_include_directories( ${UNIT_TESTS_EXEC} PUBLIC ${INC_DIR} )
  target_include_directories( ${UNIT_TESTS_EXEC} SYSTEM PUBLIC
                              ${CMAKE_BINARY_DIR}/googletest-src/googlemock/include
                              ${CMAKE_BINARY_DIR}/googletest-src/googletest/include )

  target_link_libraries     ( ${UNIT_TESTS_EXEC} gmock gmock_main ${PROJECT_LIB_NAME} )
  add_dependencies          ( ${UNIT_TESTS_EXEC} gmock gmock_main ${PROJECT_LIB_NAME} )

  set_property( TARGET ${UNIT_TESTS_EXEC} PROPERTY CXX_STANDARD 14          )
  set_property( TARGET ${UNIT_TESTS_EXEC} PROPERTY CXX_STANDARD_REQUIRED ON )

  if ( NOT MSVC )
    set_target_properties( ${UNIT_TESTS_EXEC} PROPERTIES COMPILE_FLAGS ${INTENSE_FLAGS} )
  endif( )

endif( BUILD_UNIT_TESTS )
