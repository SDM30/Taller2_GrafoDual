## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

# -- Basic configuration
cmake_minimum_required(VERSION 3.10)
project(SegmentsIntersections)
include("./baseConf.cmake")

include_directories(
  ${CMAKE_BINARY_DIR}/lib
  ${CMAKE_SOURCE_DIR}/lib
  )

# -- Packages
find_package(CGAL REQUIRED COMPONENTS Core)

# -- Executables
add_executable(pujCGAL_build_dual_graph src/build_dual_graph.cxx)
target_link_libraries(pujCGAL_build_dual_graph CGAL::CGAL)

## eof - CMakeLists.txt
