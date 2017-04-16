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
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

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

}

sanguis::creator::impl::generator_map_type const &
sanguis::creator::impl::generator_map()
{
	return
		::generators;
}
