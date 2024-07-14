cmake_minimum_required(VERSION 3.20)

project(QuestionCreator)

set(CMAKE_CXX_STANDARD 20)

# Enable Release mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Include RapidJSON from the submodule directory
set(RAPIDJSON_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/extern/rapidjson/include")
include_directories(${RAPIDJSON_INCLUDE_DIRS})

file(GLOB SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

# Set linker flags for static linking
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(QuestionCreator ${SOURCES})

# Apply Release mode specific settings
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Add optimization flags
    target_compile_options(QuestionCreator PRIVATE -O3)
    
    # Optionally, strip symbols to reduce binary size
    if (NOT WIN32)
        target_link_options(QuestionCreator PRIVATE -s)
    endif()
endif()
