cmake_minimum_required(VERSION 3.20)
find_package(SDL2 REQUIRED)

project(vehicle_simulator
        VERSION 0.0.1
        DESCRIPTION "Data-driven vehicle engine and ECU simulator"
        LANGUAGES CXX)

# =================================
# C++ STANDARD
# =================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =================================
# EXECUTABLE TARGET
# =================================
add_executable(vehicle_simulator
    src/main.cpp
    src/sim/loop.cpp
    src/engine/engine.cpp
    src/powertrain/ManualTransmission.cpp)

# =================================
# SOURCE FILES
# =================================
target_sources(vehicle_simulator
    PRIVATE
        src/main.cpp

        src/sim/Simulation.cpp
        src/vehicle/Vehicle.cpp

        src/powertrain/DummyEngine.cpp
        src/powertrain/DummyTransmission.cpp
)

# =================================
# INCLUDE DIRECTORIES
# =================================
target_include_directories(vehicle_simulator
    PRIVATE
        src
        ${SDL2_INCLUDE_DIRS}
)

# =================================
# WARNINGS (SAFE DEFAULTS)
# =================================
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(vehicle_simulator PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
elseif (MSVC)
    target_compile_options(vehicle_simulator PRIVATE
        /W4
    )
endif ()

# =================================
# DEBUG DEFINITIONS
# =================================
target_compile_definitions(vehicle_simulator
    PRIVATE
        $<$<CONFIG:Debug>:SIM_DEBUG>
)

# =================================
# OUTPUT_DIRECTORY (CLEAN)
# =================================
set_target_properties(vehicle_simulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(vehicle_simulator PRIVATE
    SDL2::SDL2
)