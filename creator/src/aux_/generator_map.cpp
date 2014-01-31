#include <sanguis/creator/name.hpp>
#include <sanguis/creator/aux_/generator_map.hpp>
#include <sanguis/creator/aux_/generator_map_type.hpp>
#include <sanguis/creator/aux_/generators/graveyard.hpp>
#include <sanguis/creator/aux_/generators/maze.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::creator::aux_::generator_map_type const generators{
	std::make_pair(
		sanguis::creator::name(
			FCPPT_TEXT("graveyard")
		),
		&sanguis::creator::aux_::generators::graveyard
	),
	std::make_pair(
		sanguis::creator::name(
			FCPPT_TEXT("maze")
		),
		&sanguis::creator::aux_::generators::maze
	)
};

}

sanguis::creator::aux_::generator_map_type const &
sanguis::creator::aux_::generator_map()
{
	return
		::generators;
}
