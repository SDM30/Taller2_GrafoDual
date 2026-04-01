// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __pujCGAL__Triangulation__h__
#define __pujCGAL__Triangulation__h__

#include <array>
#include <vector>
#include <CGAL/Surface_mesh.h>

namespace pujCGAL
{
  /**
   */
  template< class _TKernel >
  class Triangulation
  {
  public:
    using TKernel = _TKernel;
    using TReal = typename TKernel::RT;
    using TPoint = typename TKernel::Point_2;
    using TIndex = std::size_t;
    using TPoints = std::vector< TPoint >;
    using TTriangle = std::array< TIndex, 3 >;
    using TTopology = std::vector< TTriangle >;

    // Halfedge data structure types
    using TMesh = CGAL::Surface_mesh<TPoint>;
    using TVertex_index = typename TMesh::Vertex_index;
    using TFace_index = typename TMesh::Face_index;
    using THalfedge_index = typename TMesh::Halfedge_index;
    using TEdge_index = typename TMesh::Edge_index;

  public:
    Triangulation( );
    virtual ~Triangulation( );

    void clear( );
    void add_point( const TPoint& p );
    void add_triangle( const TIndex& a, const TIndex& b, const TIndex& c );

    auto geometry_begin( );
    auto geometry_begin( ) const;
    auto geometry_end( );
    auto geometry_end( ) const;

    auto topology_begin( );
    auto topology_begin( ) const;
    auto topology_end( );
    auto topology_end( ) const;

    // Representing the triangulation as a halfedge data structure
    void build_surface_mesh();
    const TMesh& get_mesh( ) const;
    // Wrappers for built-in functions
    THalfedge_index opposite( const THalfedge_index& h ) const;
    THalfedge_index next( const THalfedge_index& h ) const;
    THalfedge_index prev( const THalfedge_index& h ) const;
    TFace_index face( const THalfedge_index& h ) const;
    TVertex_index source( const THalfedge_index& h ) const;
    TVertex_index target( const THalfedge_index& h ) const;
    // External edge
    bool is_boundary_edge( const THalfedge_index& h ) const;

  protected:
    TPoints   m_Points;
    TTopology m_Topology;
    TMesh m_Mesh;
  };
} // end namespace

#include <pujCGAL/Triangulation.hxx>

#endif // __pujCGAL__Triangulation__h__

// eof - Triangulation.h
