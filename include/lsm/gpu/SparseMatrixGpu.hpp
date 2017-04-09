// SparseMatrixGpu.hpp
#pragma once
#ifndef _lsm_gpu_SparseMatrixGpu_hpp
#define _lsm_gpu_SparseMatrixGpu_hpp

#include <memory>


namespace lsm
{

template< typename T >
class SparseMatrixGpu
{

public:

  explicit
  SparseMatrixGpu();

  ~SparseMatrixGpu();


private:

  class SparseMatrixGpuImpl;
  std::unique_ptr< SparseMatrixGpuImpl > upImpl_;

};


} // namespace lsm


#endif // _lsm_gpu_SparseMatrixGpu_hpp
