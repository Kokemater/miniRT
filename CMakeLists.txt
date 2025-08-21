cmake_minimum_required(VERSION 3.5)
project(miniRT C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/glad)
add_subdirectory(libs/libft)

set(SRC
	arrays.c
	color.c
	error.c
	image.c
	intersections.c
	intersections_scene.c
	lighting.c
	main.c
	parse_arrays.c
	parse_scene.c
	parse_type.c
	parse_vec.c
	v3.c
	v3math.c
)

add_executable(miniRT ${SRC})

target_link_libraries(miniRT PUBLIC
    glfw
    glad
	m
	ft
)

target_include_directories(miniRT PRIVATE
	libs/glad/include
)

set_target_properties(miniRT PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED YES
)

