# PinguDB

## Compiling using CMake

```
# Move to source directory
cd src

# Create build folder and cd into it
mkdir build
cd build

# Create Makefiles using CMake:
cmake ..

# Build
make -j 10
```

If you use `clangd`, you can symlink `build/compile_commands.json` to root 
directory of project (`src` directory).

```
# Move to src directory
cd ..

ln -s build/compile_commands.json ./
```

## Compiling using Makefile

```
# Move to src directory
cd src

# Run make
make -j 10
```
