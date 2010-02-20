#include "resolution.hpp"
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::resolution const
sanguis::args::resolution(
	boost::program_options::variables_map const &vm
)
{
	return
		sanguis::resolution(
			vm["width"].as<
				sge::renderer::screen_unit
			>(),
			vm["height"].as<
				sge::renderer::screen_unit
			>()
		);
}
