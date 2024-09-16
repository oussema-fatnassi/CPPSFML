cmake_minimum_required(VERSION 3.10)

# Define project details
project(MainProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the paths for your project
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/testing")
include_directories(${INCLUDE_DIR})

# Add source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Create the main executable from the source files
add_executable(Main ${SRC_FILES})

# Set the build type to Debug to include debugging symbols
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Enable Address Sanitizer if desired
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        # Add Address Sanitizer compiler and linker options
        add_compile_options(-fsanitize=address -g)
        add_link_options(-fsanitize=address)
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "AddressSanitizer is not supported on Windows. Skipping sanitization.")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Fetch SFML from GitHub using FetchContent
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x  # Make sure to specify the correct version
    GIT_SHALLOW ON
)

# Make the SFML library available
FetchContent_MakeAvailable(SFML)

# Link SFML to the main executable
target_link_libraries(Main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Specify output directory for binaries directly in the build folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
