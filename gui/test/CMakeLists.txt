include(
	AwlMainGenerator
)

include_directories(
	include
)

macro(
	add_gui_test
	TEST_NAME
	DEPS
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
	)

	target_link_libraries(
		${APP_NAME}
		PRIVATE
		${sanguisgui_TARGET}
		${DEPS}
	)
endmacro()

add_gui_test(
	main
	"${Boost_FILESYSTEM_LIBRARY};${fcppt_core_TARGET};${awl_TARGET};${sgefont_TARGET};${sgeimagecolor_TARGET};${sgeimage2d_TARGET};${sgerenderer_TARGET};${sgerucksack_TARGET};${sgesystems_TARGET};${sgetimer_TARGET};${sgeviewport_TARGET};${sgewindow_TARGET}"
)
