cmake_minimum_required ( VERSION 3.6.0 )
project ( GameOfLife )

# cmake configuration variables
option( USE_CUDA OFF "Compile with GPU acceleration enabled" )

# project dirs
set( SRC_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src     )
set( INC_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( CUDA_DIR ${SRC_DIR}/cuda                     )



#
# NCurses terminal functionality to render
# game states on the command line
#
set( CURSES_NEED_NCURSES TRUE )
find_package( Curses REQUIRED )


# compile flags
if ( NOT MSVC )
  set( INTENSE_FLAGS "${INTENSE_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual"            )
  set( INTENSE_FLAGS "${INTENSE_FLAGS} -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2"      )
  set( INTENSE_FLAGS "${INTENSE_FLAGS} -Winit-self -Wmissing-declarations -Wmissing-include-dirs"   )
  set( INTENSE_FLAGS "${INTENSE_FLAGS} -Wold-style-cast -Woverloaded-virtual -Wredundant-decls"     )
  set( INTENSE_FLAGS "${INTENSE_FLAGS} -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5" )
  set( INTENSE_FLAGS "${INTENSE_FLAGS} -Wswitch-default -Wundef -Werror -Wno-unused"                )
endif( )

#
# source files for compilation
#
set(
    PROJECT_SOURCE
    ${PROJECT_SOURCE}

    ${SRC_DIR}/GameOfLife.hpp
    ${SRC_DIR}/GameOfLifeApp.hpp
    ${SRC_DIR}/GameOfLifeApp.cpp
    ${SRC_DIR}/GameOfLifeMain.cpp
    )

if ( NOT USE_CUDA )
  set( PROJECT_SOURCE ${PROJECT_SOURCE} ${SRC_DIR}/GameOfLifeImpl.cpp )
endif()

set( EXEC_NAME run${PROJECT_NAME} )

add_executable( ${EXEC_NAME} ${PROJECT_SOURCE}  )

target_include_directories( ${EXEC_NAME} PUBLIC ${CURSES_INCLUDE_DIR} ${SRC_DIR} )
target_link_libraries     ( ${EXEC_NAME} ${CURSES_LIBRARY} )

set_property( TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 14          )
set_property( TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )

if ( INTENSE_FLAGS )
  set_target_properties( ${EXEC_NAME} PROPERTIES COMPILE_FLAGS ${INTENSE_FLAGS} )
endif( )


####################
#       CUDA       #
####################
if ( USE_CUDA )

  find_package( CUDA REQUIRED )

  set(
      CUDA_SOURCE
      ${CUDA_SOURCE}

      ${SRC_DIR}/cuda/GameOfLifeImpl.cu
      )

  include_directories( ${INC_DIR} ${SRC_DIR} ${SRC_DIR}/cuda )
  include_directories( SYSTEM ${CUDA_INCLUDE_DIRS} )

  # set nvcc options
  if ( NOT MSVC )
    set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -O3 ${CUDA_COMPUTE_FLAGS} -Wno-deprecated-gpu-targets" )
    set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --compiler-options -fno-strict-aliasing -use_fast_math" )
  else( )
    set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} ${CUDA_COMPUTE_FLAGS} -Wno-deprecated-gpu-targets" )
  endif( )

  set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --std=c++11 --expt-relaxed-constexpr" )


  set( CUDA_LIB cuda${PROJECT_NAME} )

  # build CUDA library
  cuda_add_library( ${CUDA_LIB} ${CUDA_SOURCE} )

  set_property( TARGET ${CUDA_LIB} PROPERTY CXX_STANDARD 14          )
  set_property( TARGET ${CUDA_LIB} PROPERTY CXX_STANDARD_REQUIRED ON )

  if ( INTENSE_FLAGS )
    set_target_properties( ${CUDA_LIB} PROPERTIES COMPILE_FLAGS ${INTENSE_FLAGS} )
  endif( )

  target_link_libraries( ${EXEC_NAME} ${CUDA_LIB} )
  add_dependencies     ( ${EXEC_NAME} ${CUDA_LIB} )

endif( USE_CUDA )
