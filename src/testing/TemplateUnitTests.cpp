#include "lsm/SparseMatrix.hpp"
#include "lsm/gpu/SparseMatrixGpu.hpp"
#include "gmock/gmock.h"


namespace
{

constexpr float eps = 1.0e-7f;


///
/// \brief The TemplateUnitTests class
///
class TemplateUnitTests : public ::testing::Test
{

protected:

  /////////////////////////////////////////////////////////////////
  /// \brief TemplateUnitTests
  /////////////////////////////////////////////////////////////////
  TemplateUnitTests( )
  {}


  /////////////////////////////////////////////////////////////////
  /// \brief ~TemplateUnitTests
  /////////////////////////////////////////////////////////////////
  virtual
  ~TemplateUnitTests( )
  {}



};



/////////////////////////////////////////////////////////////////
/// \brief TemplatesCompile
/////////////////////////////////////////////////////////////////
TEST_F( TemplateUnitTests, TemplatesCompile )
{
  lsm::SparseMatrix< float > smf;
  lsm::SparseMatrix< double > smd;

  lsm::SparseMatrixGpu< float > smgf;
  lsm::SparseMatrixGpu< double > smgd;
}


} // namespace
