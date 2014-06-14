#include <sanguis/creator/start_name.hpp>
#include <sanguis/creator/aux_/graveyard_name.hpp>
#include <sanguis/creator/aux_/maze_name.hpp>
#include <sanguis/creator/aux_/rooms_name.hpp>
#include <sanguis/creator/aux_/generator_map.hpp>
#include <sanguis/creator/aux_/generator_map_type.hpp>
#include <sanguis/creator/aux_/generators/graveyard.hpp>
#include <sanguis/creator/aux_/generators/maze.hpp>
#include <sanguis/creator/aux_/generators/rooms.hpp>
#include <sanguis/creator/aux_/generators/start.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::creator::aux_::generator_map_type const generators{
	std::make_pair(
		sanguis::creator::start_name(),
		&sanguis::creator::aux_::generators::start
	),
	std::make_pair(
		sanguis::creator::aux_::graveyard_name(),
		&sanguis::creator::aux_::generators::graveyard
	),
	std::make_pair(
		sanguis::creator::aux_::maze_name(),
		&sanguis::creator::aux_::generators::maze
	),
	std::make_pair(
		sanguis::creator::aux_::rooms_name(),
		&sanguis::creator::aux_::generators::rooms
	)
};

}

sanguis::creator::aux_::generator_map_type const &
sanguis::creator::aux_::generator_map()
{
	return
		::generators;
}
