#include "client_sge_options.hpp"
#include "multi_sampling.hpp"
#include "resolution.hpp"
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/named.hpp>
#include <sge/window/parameters.hpp>
#include <fcppt/text.hpp>

sge::systems::list const
sanguis::args::client_sge_options(
	boost::program_options::variables_map const &vm
)
{
	return
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sanguis")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					resolution(
						vm
					),
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::multi_sample_type(
					multi_sampling(
						vm
					)
				)
			)
		)
		// TODO: replace this by capabilities
		(sge::systems::parameterless::input)
		(
			sge::systems::named(
				sge::systems::parameterless::image,
				FCPPT_TEXT("libpng")
			)
		)
		(sge::systems::parameterless::audio_player)
		(
			sge::systems::named(
				sge::systems::parameterless::font,
				FCPPT_TEXT("freetype")
			)
		);
}
