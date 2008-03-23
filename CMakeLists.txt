project (HELLO)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic -Wall -Wextra -Wconversion -Wfloat-equal -fno-strict-aliasing")
ENDIF ()

#IF (ENABLE_DEBUG AND CMAKE_COMPILER_IS_GNUCXX)
IF (CMAKE_COMPILER_IS_GNUCXX)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -g3")
ENDIF ()

ADD_DEFINITIONS(-DSGE_NARROW_STRING=1)

FILE (GLOB files *.cpp net/*.cpp client/*.cpp draw/*.cpp messages/*.cpp server/*.cpp)

add_executable(main ${files})
target_link_libraries(main boost_serialization boost_thread
	boost_program_options sgecore)
