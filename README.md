Large Sparse Matrix Library
===========================


Standalone
----------

### Download

Clone the project

```bash
git clone https://gitlab.com/LoganBarnes/LargeSparseMatrixLibrary.git
```

### Configure

Configure project using cmake

```bash
mkdir lsmBuild
cd lsmBuild
cmake ${LSM_DIR}
```

### Build

```bash
cmake --build .
```


Existing CMake Project
----------------------

Recommend including this library in the same way Google Test is used on [this blog](https://crascit.com/2015/07/25/cmake-gtest/).
