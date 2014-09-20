include(
	AwlMainGenerator
)

function(
	add_gui_test
	TEST_NAME
)
	set(
		MULTI_ARGS
		"DEPS"
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	set(
		APP_NAME
		gui_test_${TEST_NAME}
	)

	awl_utils_add_portable_executable(
		${APP_NAME}
		"sanguis_gui_test::main"
		"${TEST_NAME}.cpp"
	)

	fcppt_utils_set_target_compiler_flags(
		${APP_NAME}
	)

	target_include_directories(
		${APP_NAME}
		PRIVATE
		${awl_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}/include
	)

	target_link_libraries(
		${APP_NAME}
		PRIVATE
		${sanguis_gui_TARGET}
		${_DEPS}
	)
endfunction()

add_gui_test(
	main
	DEPS
		${Boost_FILESYSTEM_LIBRARY}
		${fcppt_core_TARGET}
		${awl_TARGET}
		${sgefont_TARGET}
		${sgeimagecolor_TARGET}
		${sgeimage2d_TARGET}
		${sgerenderer_TARGET}
		${sgerucksack_TARGET}
		${sgesystems_TARGET}
		${sgetexture_TARGET}
		${sgetimer_TARGET}
		${sgeviewport_TARGET}
		${sgewindow_TARGET}
)
