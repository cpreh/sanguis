set(
	SANGUIS_TOOLS_MERGEIMAGE_FILES
	src/main.cpp
)

sanguis_add_tool(
	mergeimage
	"${SANGUIS_TOOLS_MERGEIMAGE_FILES}"
	"${fcppt_INCLUDE_DIRS}"
	"${sanguistoolsmergeimage_TARGET};${sgeimage2d_TARGET};${sgesystems_TARGET};${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
)
