#include "lsm/gpu/SparseMatrixGpu.hpp"
#include "gmock/gmock.h"


namespace
{


///
/// \brief The GpuMatrixUnitTests class
///
class GpuMatrixUnitTests : public ::testing::Test
{

protected:

  /////////////////////////////////////////////////////////////////
  /// \brief GpuMatrixUnitTests
  /////////////////////////////////////////////////////////////////
  GpuMatrixUnitTests( )
  {}


  /////////////////////////////////////////////////////////////////
  /// \brief ~GpuMatrixUnitTests
  /////////////////////////////////////////////////////////////////
  virtual
  ~GpuMatrixUnitTests( )
  {}



};



/////////////////////////////////////////////////////////////////
/// \brief TemplatesCompile
/////////////////////////////////////////////////////////////////
TEST_F( GpuMatrixUnitTests, TemplatesCompile )
{
  lsm::SparseMatrixGpu< float > smf;
  lsm::SparseMatrixGpu< double > smd;
}


/////////////////////////////////////////////////////////////////
/// \brief FailureTest
/////////////////////////////////////////////////////////////////
TEST_F( GpuMatrixUnitTests, FailureTest )
{
  ASSERT_TRUE( true );
}


} // namespace
