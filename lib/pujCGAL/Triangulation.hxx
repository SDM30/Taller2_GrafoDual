// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __pujCGAL__Triangulation__hxx__
#define __pujCGAL__Triangulation__hxx__

// -------------------------------------------------------------------------
template< class _TKernel >
pujCGAL::Triangulation< _TKernel >::
Triangulation( )
{
  this->clear( );
}

// -------------------------------------------------------------------------
template< class _TKernel >
pujCGAL::Triangulation< _TKernel >::
~Triangulation( )
{
  this->clear( );
}

// -------------------------------------------------------------------------
template< class _TKernel >
void pujCGAL::Triangulation< _TKernel >::
clear( )
{
  this->m_Points.clear( );
  this->m_Topology.clear( );
}

// -------------------------------------------------------------------------
template< class _TKernel >
void pujCGAL::Triangulation< _TKernel >::
add_point( const TPoint& p )
{
  this->m_Points.push_back( p );
}

// -------------------------------------------------------------------------
template< class _TKernel >
void pujCGAL::Triangulation< _TKernel >::
add_triangle( const TIndex& a, const TIndex& b, const TIndex& c )
{
  this->m_Topology.push_back( { a, b, c } );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
geometry_begin( )
{
  return( this->m_Points.begin( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
geometry_begin( ) const
{
  return( this->m_Points.begin( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
geometry_end( )
{
  return( this->m_Points.end( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
geometry_end( ) const
{
  return( this->m_Points.end( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
topology_begin( )
{
  return( this->m_Topology.begin( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
topology_begin( ) const
{
  return( this->m_Topology.begin( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
topology_end( )
{
  return( this->m_Topology.end( ) );
}

// -------------------------------------------------------------------------
template< class _TKernel >
auto pujCGAL::Triangulation< _TKernel >::
topology_end( ) const
{
  return( this->m_Topology.end( ) );
}

template< class _TKernel >
void pujCGAL::Triangulation< _TKernel >::build_surface_mesh() 
{
  m_Mesh.clear();
  
  std::vector<TVertex_index> vertex_descripts(m_Points.size());
  for (TIndex i = 0; i < m_Points.size(); ++i) {
    vertex_descripts[i] = m_Mesh.add_vertex(m_Points[i]);
  }

  for (const auto& t: m_Topology) {
    m_Mesh.add_face(vertex_descripts[t[0]],
                    vertex_descripts[t[1]],
                    vertex_descripts[t[2]]);
  }
}

template< class _TKernel >
typename pujCGAL::Triangulation< _TKernel >::THalfedge_index
pujCGAL::Triangulation< _TKernel >::opposite(const THalfedge_index& h) const
{
  return m_Mesh.opposite(h);
}

template< class _TKernel >
typename pujCGAL::Triangulation< _TKernel >::THalfedge_index 
pujCGAL::Triangulation< _TKernel >::next( const THalfedge_index& h ) const
{
  return m_Mesh.next( h );
}

template< class _TKernel >
typename pujCGAL::Triangulation< _TKernel >::THalfedge_index 
pujCGAL::Triangulation< _TKernel >::prev( const THalfedge_index& h ) const
{
  return m_Mesh.prev( h );
}

template< class _TKernel >
typename pujCGAL::Triangulation< _TKernel >::TFace_index 
pujCGAL::Triangulation< _TKernel >::face( const THalfedge_index& h ) const
{
  return m_Mesh.face( h );
}

template< class _TKernel >
typename pujCGAL::Triangulation< _TKernel >::TVertex_index 
pujCGAL::Triangulation< _TKernel >::source( const THalfedge_index& h ) const
{
  return m_Mesh.source( h );
}

template< class _TKernel >
typename pujCGAL::Triangulation< _TKernel >::TVertex_index 
pujCGAL::Triangulation< _TKernel >::target( const THalfedge_index& h ) const
{
  return m_Mesh.target( h );
}

#endif // __pujCGAL__Triangulation__hxx__

// eof - Triangulation.hxx
