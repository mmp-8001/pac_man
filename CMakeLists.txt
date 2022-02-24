cmake_minimum_required(VERSION 3.17)
project(pac_man C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c objects/pacman.c objects/pacman.h main/texture.c main/texture.h common/pac_common.c common/pac_common.h objects/map.c objects/map.h objects/ghost.c objects/ghost.h main/surface.c main/surface.h objects/button.c objects/button.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(pac_man ${SOURCE_FILES})
target_link_libraries(pac_man mingw32 SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf)

add_custom_command(TARGET pac_man POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/dlls"
        $<TARGET_FILE_DIR:pac_man>)
