// SparseMatrix.hpp
#pragma once
#ifndef _lsm_gpu_SparseMatrix_hpp
#define _lsm_gpu_SparseMatrix_hpp

#include <vector>


namespace lsm
{

template< typename T >
class SparseMatrix
{

public:

  explicit
  SparseMatrix();


private:

  std::vector< T > dataPlaceholder_;

};


} // namespace lsm


#endif // _lsm_gpu_SparseMatrix_hpp
