set(
	SANGUIS_TOOLS_DRAWLEVEL_FILES
	src/main.cpp
)

sanguis_add_tool(
	drawlevel
	"${SANGUIS_TOOLS_DRAWLEVEL_FILES}"
	LINK_LIBS
		${sanguis_creator_TARGET}
		${sanguis_tiles_TARGET}
		${sgeimage2d_TARGET}
		${sgesystems_TARGET}
		${fcppt_core_TARGET}
		${Boost_FILESYSTEM_LIBRARIES}
)
