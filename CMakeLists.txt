cmake_minimum_required(VERSION 3.8)
project(Sk_iver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Diver.cpp
        Diver.h
        README.md ScreenManager.cpp ScreenManager.h Ring.cpp Ring.h HandleEvents.cpp HandleEvents.h Background.cpp Background.h Particle.cpp Particle.h Particles.cpp Particles.h Game.cpp Game.h)

add_executable(Sk_iver ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Sk_iver ${SFML_LIBRARIES})
endif()