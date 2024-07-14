# Sample toolchain file for cross-compiling to Windows from Ubuntu Linux with mingw-w64.

# Set the system name to Windows
set(CMAKE_SYSTEM_NAME Windows)

# Specify the toolchain prefix
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

# Set cross compilers for C and C++
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# Set the find root path
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

# Modify default behavior of FIND_XXX() commands
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Additional settings you might need
# Example:
# set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

# If necessary, add include directories for mingw-w64 headers
# include_directories(/usr/${TOOLCHAIN_PREFIX}/include)

# If necessary, add link directories for mingw-w64 libraries
# link_directories(/usr/${TOOLCHAIN_PREFIX}/lib)

# Example: Set compilation flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# Example: Set linker flags
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# End of toolchain file
