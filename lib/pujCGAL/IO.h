#ifndef __pujCGAL__IO__h__
#define __pujCGAL__IO__h__

#include <string>
#include <fstream>
#include <iostream>

namespace pujCGAL
{
  template< class TKernel >
  class Dual_Graph;
}


namespace pujCGAL
{
  namespace IO
  {
    /**
     */
    template< class TData >
    bool read( const std::string& fname, TData data );
 
    /**
     */
    template< class TData >
    bool save( const std::string& fname, TData data );

    template< class TKernel >
    bool save_dual_graph( const std::string& fname, 
                          const pujCGAL::Dual_Graph< TKernel >& graph );

  } // end namespace IO
} // end namespace pujCGAL

#include <pujCGAL/IO.hxx>

#endif // __pujCGAL__IO__h__
