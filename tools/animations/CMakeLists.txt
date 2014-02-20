set(
	CMAKE_AUTOMOC
	ON
)

find_package(
	Qt5Widgets
	REQUIRED
)

qt5_wrap_ui(
	MAIN_WINDOW_HPP
	ui/main_window.ui
)

set(
	SANGUIS_TOOLS_ANIMATIONS_FILES
	include/sanguis/tools/animations/main_window.hpp
	src/main.cpp
	src/main_window.cpp
	ui/main_window.ui
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(
	sanguis_tools_animations
	${SANGUIS_TOOLS_ANIMATIONS_FILES}
)

fcppt_utils_set_target_compiler_flags(
	sanguis_tools_animations
)

target_include_directories(
	sanguis_tools_animations
	PRIVATE
	${fcppt_INCLUDE_DIRS}
)

qt5_use_modules(
	sanguis_tools_animations
	Widgets
)

install(
	TARGETS
	sanguis_tools_animations
	DESTINATION
	${INSTALL_BINARY_DIR}
)
