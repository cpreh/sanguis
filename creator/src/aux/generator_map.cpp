#include <sanguis/creator/name.hpp>
#include <sanguis/creator/aux/generator_map.hpp>
#include <sanguis/creator/aux/generator_map_type.hpp>
#include <sanguis/creator/aux/generators/lines.hpp>
#include <sanguis/creator/aux/generators/maze.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::creator::aux::generator_map_type const generators{
	std::make_pair(
		sanguis::creator::name(
			FCPPT_TEXT("maze")
		),
		&sanguis::creator::aux::generators::maze
	),
	std::make_pair(
		sanguis::creator::name(
			FCPPT_TEXT("lines")
		),
		&sanguis::creator::aux::generators::lines
	)
};

}

sanguis::creator::aux::generator_map_type const &
sanguis::creator::aux::generator_map()
{
	return
		::generators;
}
