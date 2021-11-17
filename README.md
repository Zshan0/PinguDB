# PinguDB

## Compiling using CMake

If you want stack tracing, install `libunwind`:

```
apt-get install binutils-dev
```

```
# Create build folder and cd into it
mkdir build
cd build

# Create Makefiles using CMake:
cmake ../src

# Build
make -j 10
```

## Additional features in CMake build

1. If you use `clangd`, you can symlink `build/compile_commands.json` to `src`
directory.

```
ln -s ../build/compile_commands.json
```

1. To enable stack tracing, build like this:

```
# Get backward-cpp submodule
git submodule update --init --recursive

# Get "libunwind"
apt-get install binutils-dev
```

Then build using the following CMake flags:

```
cmake -DCMAKE_BUILD_TYPE=Debug ../src
```

## Compiling using Makefile

```
# Move to src directory
cd src

# Run make
make -j 10
```
