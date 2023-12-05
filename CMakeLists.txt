set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.0)

project(visula)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Find libsndfile
find_package(SndFile REQUIRED)

add_executable(visula main.cpp)

# Link the required libraries
target_link_libraries(visula
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
    ${SNDFILE_LIBRARIES}
)

# Ensure our executable can find the include directories
target_include_directories(visula PRIVATE
    ${SNDFILE_INCLUDE_DIRS}
)

install(TARGETS visula RUNTIME DESTINATION bin)
