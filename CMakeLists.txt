cmake_minimum_required(VERSION 3.0.0)
project(st)

# install in ~/.local
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

add_definitions(-DVERSION="0.8.2" -std=c99 -D_XOPEN_SOURCE=600)

include_directories(
    /usr/include/freetype2
    /usr/include/libpng16
)
add_library(st_util st.c boxdraw.c)
target_link_libraries(st_util freetype fontconfig X11 Xft rt m)

add_executable(st x.c)
target_link_libraries(st st_util util freetype fontconfig X11 Xft rt m)

install(TARGETS st)