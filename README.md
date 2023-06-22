# PyTorch-Direct
This repo mainly contains the modified source code of PyTorch. For a more comprehensive explanation of PyTorch-Direct, please go to [here](https://github.com/K-Wu/pytorch-direct_dgl).




## Installation


### From Source

If you are installing from source, you will need Python 3.6.2 or later and a C++14 compiler. Also, we highly recommend installing an [Anaconda](https://www.anaconda.com/distribution/#download-section) environment.
You will get a high-quality BLAS library (MKL) and you get controlled dependency versions regardless of your Linux distro.

Once you have [Anaconda](https://www.anaconda.com/distribution/#download-section) installed, here are the instructions.

If you want to compile with CUDA support, install
- [NVIDIA CUDA](https://developer.nvidia.com/cuda-downloads) 9.2 or above
- [NVIDIA cuDNN](https://developer.nvidia.com/cudnn) v7 or above
- [Compiler](https://gist.github.com/ax3l/9489132) compatible with CUDA
Note: You could refer to the [cuDNN Support Matrix](https://docs.nvidia.com/deeplearning/cudnn/pdf/cuDNN-Support-Matrix.pdf) for cuDNN versions with the various supported CUDA, CUDA driver and NVIDIA hardwares

If you want to disable CUDA support, export environment variable `USE_CUDA=0`.
Other potentially useful environment variables may be found in `setup.py`.

If you are building for NVIDIA's Jetson platforms (Jetson Nano, TX1, TX2, AGX Xavier), Instructions to install PyTorch for Jetson Nano are [available here](https://devtalk.nvidia.com/default/topic/1049071/jetson-nano/pytorch-for-jetson-nano/)


#### Install Dependencies

Common
```bash
conda install -y numpy ninja pyyaml mkl mkl-include setuptools cmake cffi typing_extensions future six requests dataclasses
```

On Linux
```bash
# Add LAPACK support for the GPU if needed
conda install -y -c pytorch magma-cuda113 # or the magma-cuda* that matches your CUDA version from https://anaconda.org/pytorch/repo
```

On MacOS
```bash
# Add these packages if torch.distributed is needed
conda install pkg-config libuv
```

On Windows
```bash
# Add these packages if torch.distributed is needed.
# Distributed package support on Windows is a prototype feature and is subject to changes.
conda install -c conda-forge libuv=1.39
```

#### Get the PyTorch Source
```bash
#git clone --recursive https://github.com/pytorch/pytorch
git clone --recursive https://github.com/K-Wu/pytorch-direct.git
cd pytorch-direct
# if you are updating an existing checkout
git submodule sync
git submodule update --init --recursive
```

#### Install PyTorch
On Linux
```bash
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
export CMAKE_PREFIX_PATH=${CONDA_PREFIX:-"$(dirname $(which conda))/../"}
python setup.py install
```

Note that if you are using [Anaconda](https://www.anaconda.com/distribution/#download-section), you may experience an error caused by the linker:

```plaintext
build/temp.linux-x86_64-3.7/torch/csrc/stub.o: file not recognized: file format not recognized
collect2: error: ld returned 1 exit status
error: command 'g++' failed with exit status 1
```

This is caused by `ld` from Conda environment shadowing the system `ld`. You should use a newer version of Python that fixes this issue. The recommended Python version is 3.6.10+, 3.7.6+ and 3.8.1+.

On macOS
```bash
export CMAKE_PREFIX_PATH=${CONDA_PREFIX:-"$(dirname $(which conda))/../"}
MACOSX_DEPLOYMENT_TARGET=10.9 CC=clang CXX=clang++ python setup.py install
```

Each CUDA version only supports one particular XCode version. The following combinations have been reported to work with PyTorch.

| CUDA version | XCode version |
| ------------ | ------------- |
| 10.0         | XCode 9.4     |
| 10.1         | XCode 10.1    |


On Windows

Build with CPU

It's fairly easy to build with CPU. Visual Studio 2019 version 16.7.6 (MSVC toolchain version 14.27) or higher is recommended.

Build with CUDA

[NVTX](https://docs.nvidia.com/gameworks/content/gameworkslibrary/nvtx/nvidia_tools_extension_library_nvtx.htm) is needed to build Pytorch with CUDA.
NVTX is a part of CUDA distributive, where it is called "Nsight Compute". To install it onto already installed CUDA run CUDA installation once again and check the corresponding checkbox.
Make sure that CUDA with Nsight Compute is installed after Visual Studio.

Currently, VS 2017 / 2019, and Ninja are supported as the generator of CMake. If `ninja.exe` is detected in `PATH`, then Ninja will be used as the default generator, otherwise, it will use VS 2017 / 2019.
<br/> If Ninja is selected as the generator, the latest MSVC will get selected as the underlying toolchain.

CUDA, MSVC, and PyTorch versions are interdependent; please install matching versions from this table:
| CUDA version | Newest supported VS version                             | PyTorch version |
| ------------ | ------------------------------------------------------- | --------------- |
| 9.2          | Visual Studio 2017 Update 5 (15.5) (`_MSC_VER` <= 1912) |  0.4.1 ~ 1.5.1  |
| 10.1         | Visual Studio 2019 (16.X) (`_MSC_VER` < 1930)           |  1.3.0 ~ 1.7.0  |
| 10.2         | Visual Studio 2019 (16.X) (`_MSC_VER` < 1930)           |  1.5.0 ~ 1.7.0  |
| 11.0         | Visual Studio 2019 (16.X) (`_MSC_VER` < 1930)           |      1.7.0      |

Note: There's a [compilation issue](https://github.com/oneapi-src/oneDNN/issues/812) in several Visual Studio 2019 versions since 16.7.1, so please make sure your Visual Studio 2019 version is not in 16.7.1 ~ 16.7.5

Additional libraries such as
[Magma](https://developer.nvidia.com/magma), [oneDNN, a.k.a MKLDNN or DNNL](https://github.com/oneapi-src/oneDNN), and [Sccache](https://github.com/mozilla/sccache) are often needed. Please refer to the [installation-helper](https://github.com/pytorch/pytorch/tree/master/.jenkins/pytorch/win-test-helpers/installation-helpers) to install them.

You can refer to the [build_pytorch.bat](https://github.com/pytorch/pytorch/blob/master/.jenkins/pytorch/win-test-helpers/build_pytorch.bat) script for some other environment variables configurations


```cmd
cmd

:: [Optional] If you want to build with the VS 2017 generator for old CUDA and PyTorch, please change the value in the next line to `Visual Studio 15 2017`.
:: Note: This value is useless if Ninja is detected. However, you can force that by using `set USE_NINJA=OFF`.
set CMAKE_GENERATOR=Visual Studio 16 2019

:: Read the content in the previous section carefully before you proceed.
:: [Optional] If you want to override the underlying toolset used by Ninja and Visual Studio with CUDA, please run the following script block.
:: "Visual Studio 2019 Developer Command Prompt" will be run automatically.
:: Make sure you have CMake >= 3.12 before you do this when you use the Visual Studio generator.
set CMAKE_GENERATOR_TOOLSET_VERSION=14.27
set DISTUTILS_USE_SDK=1
for /f "usebackq tokens=*" %i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -version [15^,16^) -products * -latest -property installationPath`) do call "%i\VC\Auxiliary\Build\vcvarsall.bat" x64 -vcvars_ver=%CMAKE_GENERATOR_TOOLSET_VERSION%

:: [Optional] If you want to override the CUDA host compiler
set CUDAHOSTCXX=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\HostX64\x64\cl.exe

python setup.py install

```

##### Adjust Build Options (Optional)

You can adjust the configuration of cmake variables optionally (without building first), by doing
the following. For example, adjusting the pre-detected directories for CuDNN or BLAS can be done
with such a step.

On Linux
```bash
export CMAKE_PREFIX_PATH=${CONDA_PREFIX:-"$(dirname $(which conda))/../"}
python setup.py build --cmake-only
ccmake build  # or cmake-gui build
```

On macOS
```bash
export CMAKE_PREFIX_PATH=${CONDA_PREFIX:-"$(dirname $(which conda))/../"}
MACOSX_DEPLOYMENT_TARGET=10.9 CC=clang CXX=clang++ python setup.py build --cmake-only
ccmake build  # or cmake-gui build
```

### Docker Image

#### Using pre-built images

You can also pull a docker image from Docker Hub and run with docker v19.03+

Use this image, uninstall pytorch, and install our project.
```bash
docker run --gpus all --rm -ti --ipc=host pytorch/pytorch:1.11.0-cuda11.3-cudnn8-devel
pip uninstall -y torch torchelastic torchtext torchvision
```


Please note that PyTorch uses shared memory to share data between processes, so if torch multiprocessing is used (e.g.
for multithreaded data loaders) the default shared memory segment size that the container runs with is not enough, and you
should increase shared memory size either with `--ipc=host` or `--shm-size` command line options to `nvidia-docker run`.

#### Building the image yourself

**NOTE:** Must be built with a docker version > 18.06

The `Dockerfile` is supplied to build images with Cuda support and cuDNN v7.
You can pass `PYTHON_VERSION=x.y` make variable to specify which Python version is to be used by Miniconda, or leave it
unset to use the default.
```bash
make -f docker.Makefile
# images are tagged as docker.io/${your_docker_username}/pytorch
```




## License

PyTorch has a BSD-style license, as found in the [LICENSE](LICENSE) file.
