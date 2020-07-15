cmake_minimum_required(VERSION 3.16)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)

set(FLAGS "-L -lmlx -lXext -lX11 -lm")
set(LIBX libmlx)
set(LIBX_PATH ../minilibx/libmlx.a)


add_library(${LIBX} STATIC IMPORTED)
set_property(TARGET ${LIBX} PROPERTY IMPORTED_LOCATION ${LIBX_PATH})

add_executable(${PROJECT_NAME}  src/wolf3d.c
                                src/test_functions.c
                                src/utilits.c
                                src/check_file.c
                                src/create_map.c
                                src/minimap.c
                                src/render_line.c
                                src/ray_cast.c
                                src/draw_image.c
        src/hooks.c
                                src/move.c)

target_link_libraries(${PROJECT_NAME} ${LIBX} ${FLAGS})