Large Sparse Matrix Library
===========================

Current Status
--------------

| System | Compiler | Status |
| ------ | -------- | ------ |
| MacOSX, Linux 64 bits | Clang 3.4, Clang 3.8, GCC 4.9 | [![Travis CI](https://travis-ci.org/LoganBarnes/lsm.svg?branch=master)](https://travis-ci.org/LoganBarnes/lsm)|

Standalone Usage
----------------

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


Existing CMake Project Integration
----------------------------------

Recommend including this library in the same way Google Test is used on [this blog](https://crascit.com/2015/07/25/cmake-gtest/).
