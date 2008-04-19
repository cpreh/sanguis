project (HELLO)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic -Wall -Wextra -Wconversion -Wfloat-equal")
ENDIF ()

IF (ENABLE_DEBUG AND CMAKE_COMPILER_IS_GNUCXX)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF ()

FILE (GLOB files 
	*.cpp
	net/*.cpp
	client/*.cpp
	client_messages/*.cpp
	draw/*.cpp
	messages/*.cpp
	server/*.cpp
	server/projectiles/*.cpp
	server/weapons/*.cpp
	load/model/*.cpp
	load/resource/*.cpp)

add_executable(main ${files})
target_link_libraries(main boost_serialization boost_thread
	boost_program_options sgecore)
