#include <sanguis/client/args/optional_resolution.hpp>
#include <sanguis/client/args/resolution.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::args::optional_resolution
sanguis::client::args::resolution(
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
			sanguis::client::args::optional_resolution(
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
			sanguis::client::args::optional_resolution()
		;
}
