#include <sanguis/args/resolution.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::args::optional_resolution const
sanguis::args::resolution(
	boost::program_options::variables_map const &_vm
)
{
	return
		_vm.count(
			"width"
		)
		&&
		_vm.count(
			"height"
		)
		?
			args::optional_resolution(
				sge::renderer::screen_size(
					_vm["width"].as<
						sge::renderer::screen_unit
					>(),
					_vm["height"].as<
						sge::renderer::screen_unit
					>()
				)
			)
		:
			args::optional_resolution();
}
