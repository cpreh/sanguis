set(
	SANGUIS_COLLISION_BENCH_MAIN_FILES
	collision/bench/main.cpp
)

fcppt_utils_append_source_dir_and_make_groups(
	"${SANGUIS_COLLISION_BENCH_MAIN_FILES}"
	SANGUIS_COLLISION_BENCH_MAIN_FILES_ABS
)

add_executable(
	collision_bench_main
	${SANGUIS_COLLISION_BENCH_MAIN_FILES_ABS}
)

fcppt_utils_set_target_compiler_flags(
	collision_bench_main
)

target_include_directories(
	collision_bench_main
	PRIVATE
	${Boost_INCLUDE_DIRS}
	${fcppt_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/creator/include
)

target_link_libraries(
	collision_bench_main
	PRIVATE
	${sanguis_collision_TARGET}
)
