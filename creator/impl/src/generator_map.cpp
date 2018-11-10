#include <sanguis/creator/start_name.hpp>
#include <sanguis/creator/impl/generator_map.hpp>
#include <sanguis/creator/impl/generator_map_type.hpp>
#include <sanguis/creator/impl/graveyard_name.hpp>
#include <sanguis/creator/impl/maze_name.hpp>
#include <sanguis/creator/impl/rooms_name.hpp>
#include <sanguis/creator/impl/generators/graveyard.hpp>
#include <sanguis/creator/impl/generators/maze.hpp>
#include <sanguis/creator/impl/generators/rooms.hpp>
#include <sanguis/creator/impl/generators/start.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

sanguis::creator::impl::generator_map_type const generators{
	std::make_pair(
		sanguis::creator::start_name(),
		&sanguis::creator::impl::generators::start
	),
	std::make_pair(
		sanguis::creator::impl::graveyard_name(),
		&sanguis::creator::impl::generators::graveyard
	),
	std::make_pair(
		sanguis::creator::impl::maze_name(),
		&sanguis::creator::impl::generators::maze
	),
	std::make_pair(
		sanguis::creator::impl::rooms_name(),
		&sanguis::creator::impl::generators::rooms
	)
};

FCPPT_PP_POP_WARNING

}

sanguis::creator::impl::generator_map_type const &
sanguis::creator::impl::generator_map()
{
	return
		::generators;
}
