# PinguDB

## Compiling using CMake

```
# Create build folder and cd into it
mkdir build
cd build

# Create Makefiles using CMake:
cmake ../src

# Build
make -j 10
```

If you use `clangd`, you can symlink `build/compile_commands.json` to `src`
directory.

```
ln -s compile_commands.json ../src/
```

## Compiling using Makefile

```
# Move to src directory
cd src

# Run make
make -j 10
```
