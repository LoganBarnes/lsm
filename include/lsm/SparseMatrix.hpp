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

  std::vector< unsigned long > rowIndices_;
  std::vector< unsigned long > colIndices_;
  std::vector< T > values_;

};


} // namespace lsm


#endif // _lsm_gpu_SparseMatrix_hpp
