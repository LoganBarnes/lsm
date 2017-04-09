// SparseMatrix.cpp
#include "lsm/SparseMatrix.hpp"


namespace lsm
{

template< typename T >
SparseMatrix< T >::SparseMatrix()
{}


} // namespace lsm

template class lsm::SparseMatrix< float >;
template class lsm::SparseMatrix< double >;
