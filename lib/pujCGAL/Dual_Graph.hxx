#ifndef __pujCGAL__Dual_Graph__hxx__
#define __pujCGAL__Dual_Graph__hxx__

#include <algorithm>  
#include <limits>     
#include <set>
#include <fstream>   
#include <iostream>   
#include "Dual_Graph.h"


template< class _TKernel >
void pujCGAL::Dual_Graph< _TKernel >::clear( )
{
  m_Nodes.clear();
  m_Edges.clear();
}

template< class _TKernel >
void pujCGAL::Dual_Graph< _TKernel >::add_node( const TPoint& point )
{
  m_Nodes.push_back( point );
}

template< class _TKernel >
void pujCGAL::Dual_Graph< _TKernel >::add_edge( TIndex u, TIndex v )
{
  if ( u > v ) std::swap( u, v );
  m_Edges.emplace_back( u, v );
}

template< class _TKernel >
template< class _TTriangulation >
void pujCGAL::Dual_Graph< _TKernel >::build_from_triangulation( 
    const _TTriangulation& triangulation )
{
  using TFace_index = typename _TTriangulation::TFace_index;
  using THalfedge_index = typename _TTriangulation::THalfedge_index;
  using TMesh = typename _TTriangulation::TMesh;
  
  clear();
  
  const auto& mesh = triangulation.get_mesh();
  
  if ( mesh.number_of_faces() == 0 )
  {
    std::cerr << "Error: empty triangulation" << std::endl;
    return;
  }
  
  std::vector<TFace_index> face_indices;
  
  for ( auto face : mesh.faces() )
  {
    // Compute barycenter
    THalfedge_index h = mesh.halfedge( face );
    TPoint sum( 0, 0 );
    int count = 0;
    
    do
    {
      auto v = mesh.target( h );
      const auto& p = mesh.point( v );
      sum = TPoint( sum.x() + p.x(), sum.y() + p.y() );
      count++;
      h = mesh.next( h );
    }
    while ( h != mesh.halfedge( face ) );
    
    TPoint barycenter( sum.x() / count, sum.y() / count );
    
    add_node( barycenter );
    face_indices.push_back( face );
  }
  
  // Compute infinite point
  TReal max_x = std::numeric_limits<TReal>::lowest();
  TReal max_y = std::numeric_limits<TReal>::lowest();
  
  for ( auto it = triangulation.geometry_begin();
        it != triangulation.geometry_end();
        ++it )
  {
    if ( it->x() > max_x ) max_x = it->x();
    if ( it->y() > max_y ) max_y = it->y();
  }
  
  TPoint infinite_point( max_x * 2.0, max_y * 2.0 );
  TIndex infinite_idx = m_Nodes.size();
  add_node( infinite_point );
  
  // Create edges in dual graph
  std::set<TEdge> edge_set;
  
  for ( std::size_t i = 0; i < face_indices.size(); ++i )
  {
    TFace_index face = face_indices[i];
    THalfedge_index h = mesh.halfedge( face );
    THalfedge_index start = h;
    
    do
    {
      THalfedge_index opposite_h = mesh.opposite( h );
      TFace_index adj_face = mesh.face( opposite_h );
      
      if ( adj_face == TMesh::null_face() )
      {
        // External edge
        TIndex u = i;
        TIndex v = infinite_idx;
        if ( u > v ) std::swap( u, v );
        edge_set.insert( std::make_pair( u, v ) );
      }
      else
      {
        // Internal edge
        auto it = std::find( face_indices.begin(), face_indices.end(), adj_face );
        // Get adjacent face index, only inserting once
        // The edges in the graph have no direction
        TIndex j = std::distance( face_indices.begin(), it );
        if ( i < j )
        {
          edge_set.insert( std::make_pair( i, j ) );
        }
      
      }
      
      h = mesh.next( h );
    } while ( h != start );
  }
  

  m_Edges.assign( edge_set.begin(), edge_set.end() );
}

#endif // __pujCGAL__Dual_Graph__hxx__