cmake_minimum_required(VERSION 3.31)
project(Demo
    VERSION 1.0
    LANGUAGES CXX)

file(COPY
    static/fonts/futura.ttf
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/static/fonts)
file(COPY
    static/img/BluRayLogo.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/static/img)
file(COPY
    static/img/CDLogo.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/static/img)
file(COPY
    static/img/DVDLogo.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/static/img)
file(COPY
   config.txt
   DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

configure_file(
    config.txt
    ${CMAKE_CURRENT_BINARY_DIR}/config.txt
    COPYONLY
)

add_subdirectory(dependencies)
add_subdirectory(src)