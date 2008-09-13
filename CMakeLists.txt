project (HELLO)

INCLUDE (CheckCXXSourceRuns)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

CHECK_CXX_SOURCE_RUNS(
	"#include <sge/config.h>
	 #include <cstdlib>
	 int main() {
	 #ifdef SGE_HAVE_VARIADIC_TEMPLATES
	 	return 0;
	 #else
	 	return EXIT_FAILURE;
	 #endif
	 }"
	 HAVE_VARIADIC_TEMPLATES)

FIND_PACKAGE(Boost 1.36.0 COMPONENTS
	filesystem
	serialization
	thread,
	program_options)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal -Winit-self -Wold-style-cast")
ENDIF ()

IF (ENABLE_DEBUG AND CMAKE_COMPILER_IS_GNUCXX)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF ()

IF (HAVE_VARIADIC_TEMPLATES)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ENDIF ()

FILE (GLOB files 
	*.cpp
	net/*.cpp
	client/*.cpp
	client_messages/*.cpp
	draw/*.cpp
	draw/factory/*.cpp
	messages/*.cpp
	load/*.cpp
	load/model/*.cpp
	load/resource/*.cpp
	server/*.cpp
	server/ai/*.cpp
	server/auras/*.cpp
	server/entities/*.cpp
	server/entities/enemies/*.cpp
	server/entities/pickups/*.cpp
	server/entities/projectiles/*.cpp
	server/perks/*.cpp
	server/states/*.cpp
	server/waves/*.cpp
	server/weapons/*.cpp)

add_executable(main ${files})
#add_executable(shader_main shader_main.cpp file_to_string.cpp file_size.cpp)
#target_link_libraries(shader_main sgecore)
target_link_libraries(main boost_serialization boost_thread
	boost_program_options sgecore)
