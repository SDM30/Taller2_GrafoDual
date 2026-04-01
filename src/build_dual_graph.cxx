// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <pujCGAL/IO.h>
#include <pujCGAL/Polygon.h>
#include <pujCGAL/Triangulation.h>
#include <pujCGAL/Dual_Graph.h>
 
int main( int argc, char** argv )
{
  using TKernel = CGAL::Exact_predicates_inexact_constructions_kernel;
  using TPolygon = pujCGAL::Polygon< TKernel >;
  using TTriangulation = pujCGAL::Triangulation< TKernel >;
  using TPoint = TPolygon::TPoint;

  TPolygon polygon;
  TTriangulation mesh;
  pujCGAL::IO::read( argv[ 1 ], polygon );

  std::cout << "Area = " << polygon.area( ) << std::endl;
  polygon.guarantee_CCW( );
  std::cout << "Corrected area = " << polygon.area( ) << std::endl;

  pujCGAL::triangulate( mesh, polygon );
  pujCGAL::IO::save( argv[ 2 ], mesh );

  mesh.build_surface_mesh();

  pujCGAL::Dual_Graph< TKernel > dual_graph;
  dual_graph.build_from_triangulation( mesh );

  pujCGAL::IO::save_dual_graph(argv[3], dual_graph);

  // const auto& mesh_test = mesh.get_mesh();
  // int counter_exed = 0;
  // for ( auto face : mesh_test.faces( ) )
  // {
  //   auto h = mesh_test.halfedge( face );
  //   auto start = h;
  //   do
  //   {
  //     if ( mesh.is_boundary_edge( h ) )
  //     {
  //       counter_exed ++;
  //       std::cout << "Arista de frontera encontrada" << std::endl;
  //     }
  //     h = mesh.next( h );
  //   }
  //   while ( h != start );
  // }
  // std::cout << "contador aristas exteriores = " << counter_exed << std::endl;
  

  return( EXIT_SUCCESS );
}

// eof - triangulate.cxx
