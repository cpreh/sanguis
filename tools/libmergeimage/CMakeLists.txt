set(
	SANGUIS_TOOLS_LIBMERGEIMAGE_FILES
	include/sanguis/tools/libmergeimage/merge_paths.hpp
	src/merge_paths.cpp
)

sanguis_generate_symbol_header_base(
	sanguistoolsmergeimage
	SANGUIS_TOOLS_LIBMERGEIMAGE
	sanguis/tools/libmergeimage
)

sanguis_add_library(
	sanguistoolsmergeimage
	"${SANGUIS_TOOLS_LIBMERGEIMAGE_FILES}"
	"${sanguismodel_TARGET};${fcppt_core_TARGET};${fcppt_filesystem_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
)
