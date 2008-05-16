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

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal")
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
	messages/*.cpp
	server/*.cpp
	server/ai/*.cpp
	server/entities/*.cpp
	server/entities/auras/*.cpp
	server/entities/projectiles/*.cpp
	server/perks/*.cpp
	server/states/*.cpp
	server/weapons/*.cpp
	load/model/*.cpp
	load/resource/*.cpp)

add_executable(main ${files})
target_link_libraries(main boost_serialization boost_thread
	boost_program_options sgecore)
