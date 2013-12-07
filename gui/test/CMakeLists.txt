include(
	AwlMainGenerator
)

add_definitions(
	${awl_DEFINITIONS}
)

include_directories(
	include
)

macro(
	add_gui_test
	TEST_NAME
	DEPS
)
	awl_utils_add_portable_executable(
		gui_test_${TEST_NAME}
		"sanguis_gui_test::main"
		"${TEST_NAME}.cpp"
	)

	target_link_libraries(
		gui_test_${TEST_NAME}
		sanguisgui
		"${DEPS}"
	)
endmacro()

add_gui_test(
	main
	"${fcppt_core_TARGET};${awl_TARGET};${sgefont_TARGET};${sgeimagecolor_TARGET};${sgerenderer_TARGET};${sgerucksack_TARGET};${sgesystems_TARGET};${sgetimer_TARGET};${sgeviewport_TARGET};${sgewindow_TARGET}"
)
