#include <sanguis/args/screen_mode.hpp>
#include <sanguis/args/optional_resolution.hpp>
#include <sanguis/args/resolution.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/fullscreen.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/windowed.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>

sge::renderer::screen_mode const
sanguis::args::screen_mode(
	boost::program_options::variables_map const &_vm
)
{
	args::optional_resolution const res(
		args::resolution(
			_vm
		)
	);

	return
		res
		?
			sge::renderer::screen_mode(
				sge::renderer::fullscreen(
					sge::renderer::display_mode(
						*res,
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					)
				)
			)
		:
			sge::renderer::screen_mode(
				sge::renderer::windowed(
					sge::renderer::bit_depth::depth32
				)
			);
}
