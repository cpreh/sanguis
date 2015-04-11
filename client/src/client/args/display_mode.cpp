#include <sanguis/client/args/display_mode.hpp>
#include <sanguis/client/args/resolution.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::optional_object const
sanguis::client::args::display_mode(
	boost::program_options::variables_map const &_vm
)
{
	return
		fcppt::optional_bind_construct(
			sanguis::client::args::resolution(
				_vm
			),
			[](
				sge::renderer::screen_size const _res
			)
			{
				return
					sge::renderer::display_mode::object(
						sge::renderer::display_mode::pixel_size(
							_res
						),
						sge::renderer::display_mode::optional_dimensions(),
						sge::renderer::display_mode::optional_refresh_rate()
					);
			}
		);
}
