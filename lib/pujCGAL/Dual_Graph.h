#ifndef __pujCGAL__Dual_Graph__h__
#define __pujCGAL__Dual_Graph__h__

#include <vector>
#include <set>
#include <utility>

namespace pujCGAL 
{
    template< class _TKernel >
    class Dual_Graph 
    {
    public:
        using TKernel = _TKernel;
        using TReal = typename TKernel::RT;
        using TPoint = typename TKernel::Point_2;
        using TIndex = std::size_t;
        using TEdge = std::pair<TIndex, TIndex>;
        
    public:
        Dual_Graph( ) = default;
        virtual ~Dual_Graph( ) = default;
        
        template< class _TTriangulation >
        void build_from_triangulation( const _TTriangulation& triangulation );
        
        void add_node( const TPoint& point );
        void add_edge( TIndex u, TIndex v );
        
        const std::vector<TPoint>& get_nodes( ) const { return m_Nodes; }
        const std::vector<TEdge>& get_edges( ) const { return m_Edges; }
        
        TIndex number_of_nodes( ) const { return m_Nodes.size(); }
        TIndex number_of_edges( ) const { return m_Edges.size(); }
        
        void clear( );
    
    private:
        std::vector<TPoint> m_Nodes;   
        std::vector<TEdge> m_Edges;
    };
} // end namespace

#include <pujCGAL/Dual_Graph.hxx>

#endif // __pujCGAL__Dual_Graph__h__