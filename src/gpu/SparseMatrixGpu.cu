// SparseMatrixGpu.cpp
#include "lsm/gpu/SparseMatrixGpu.hpp"

#include <iostream>
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include "gpu/helper_cuda.h"


namespace lsm
{


namespace
{

///
/// \brief The CudaEnvironment struct
///
struct CudaEnvironment
{

  CudaEnvironment( )
  {
    if ( findCudaDevice( 0, 0, false ) < 0 )
    {
      throw std::runtime_error( "No CUDA capable devices found" );
    }

#ifdef VERBOSE_PRINT
      std::cout << "CUDA device initialized" << std::endl;
#endif
  }


  ~CudaEnvironment( )
  {
    // cudaDeviceReset causes the driver to clean up all state. While
    // not mandatory in normal operation, it is good practice.  It is also
    // needed to ensure correct operation when the application is being
    // profiled. Calling cudaDeviceReset causes all profile data to be
    // flushed before the application exits
    cudaDeviceReset( );

#ifdef VERBOSE_PRINT
    std::cout << "CUDA device reset" << std::endl;
#endif
  }


};

///
/// \brief cudaEnvironment
///
const CudaEnvironment cudaEnvironment;

} // namespace


template< typename T >
class SparseMatrixGpu< T >::SparseMatrixGpuImpl
{

public:

  explicit
  SparseMatrixGpuImpl();


private:

  thrust::device_vector< T > dataPlaceholder_;

};

template< typename T >
SparseMatrixGpu< T >::SparseMatrixGpuImpl::SparseMatrixGpuImpl()
  : dataPlaceholder_( 10 ) // temp init size
{}


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

template< typename T >
SparseMatrixGpu< T >::SparseMatrixGpu()
  : upImpl_( new SparseMatrixGpuImpl() )
{}


template< typename T >
SparseMatrixGpu< T >::~SparseMatrixGpu()
{}


} // namespace lsm

template class lsm::SparseMatrixGpu< float >;
template class lsm::SparseMatrixGpu< double >;
