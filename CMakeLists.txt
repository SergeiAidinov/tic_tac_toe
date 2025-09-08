cmake_minimum_required(VERSION 3.25)
project(tic_tac_toe C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER gcc)
# Пути к заголовкам
include_directories(/usr/local/include)

# Пути к библиотекам
link_directories(/usr/local/lib)
add_executable(tic_tac_toe)
target_sources(tic_tac_toe PRIVATE main.c)
find_package(SDL3)
target_link_libraries(tic_tac_toe PRIVATE SDL3::SDL3)
target_link_options(tic_tac_toe PRIVATE -dynamic)


add_executable(#tic_tac_toe
        src/main.c
        src/utils.c
        src/logic.c
        src/graphics_interface.c
        src/gameplay.c
        src/console_interface.c
)

