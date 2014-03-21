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
	include/sanguis/tools/animations/exception.hpp
	include/sanguis/tools/animations/int_to_delay.hpp
	include/sanguis/tools/animations/main_window.hpp
	include/sanguis/tools/animations/optional_animation_ref.hpp
	include/sanguis/tools/animations/optional_animation_ref_fwd.hpp
	include/sanguis/tools/animations/qtutil/from_fcppt_string.hpp
	include/sanguis/tools/animations/qtutil/from_sge_color_format.hpp
	include/sanguis/tools/animations/qtutil/image_from_view.hpp
	include/sanguis/tools/animations/qtutil/image_unique_ptr.hpp
	include/sanguis/tools/animations/qtutil/to_fcppt_string.hpp
	include/sanguis/tools/animations/sge_systems.hpp
	include/sanguis/tools/animations/sge_systems_fwd.hpp
	src/exception.cpp
	src/int_to_delay.cpp
	src/main.cpp
	src/main_window.cpp
	src/qtutil/from_fcppt_string.cpp
	src/qtutil/from_sge_color_format.cpp
	src/qtutil/image_from_view.cpp
	src/qtutil/to_fcppt_string.cpp
	ui/main_window.ui
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
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
	sanguis_tools_animations
	${sanguismodel_TARGET}
	${sgecore_TARGET}
	${sgeimagecolor_TARGET}
	${sgeimage2d_TARGET}
	${sgesystems_TARGET}
	${fcppt_core_TARGET}
	${Boost_FILESYSTEM_LIBRARIES}
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
