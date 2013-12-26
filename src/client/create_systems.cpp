#include <sanguis/app_name.hpp>
#include <sanguis/company_name.hpp>
#include <sanguis/args/display_mode.hpp>
#include <sanguis/args/log_level.hpp>
#include <sanguis/args/multi_sampling.hpp>
#include <sanguis/client/create_systems.hpp>
#include <sanguis/client/systems.hpp>
#include <sanguis/client/systems_unique_ptr.hpp>
#include <sge/audio/loader_capabilities_field.hpp>
#include <sge/config/log_path.hpp>
#include <sge/config/own_app_name.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/log/location.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/title.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::systems_unique_ptr
sanguis::client::create_systems(
	boost::program_options::variables_map const &_vm
)
{
	sge::window::dim const dimensions(
		1024,
		768
	);

	return
		fcppt::make_unique_ptr<
			sanguis::client::systems
		>(
			sge::systems::make_list
			(
				sge::systems::config()
				.log_settings(
					sge::systems::log_settings(
						sge::log::location(),
						sanguis::args::log_level(
							_vm
						)
					)
					.redirect(
						sge::config::log_path(
							sanguis::company_name(),
							sge::config::own_app_name()
						)
					)
				)
			)
			(
				sge::systems::window(
					sge::window::parameters(
						sge::window::title(
							sanguis::app_name()
						),
						dimensions
					)
				)
			)
			(
				sge::systems::renderer(
					sge::renderer::parameters::object(
						sge::renderer::pixel_format::object(
							sge::renderer::pixel_format::color::depth32,
							sge::renderer::pixel_format::depth_stencil::d24s8,
							sanguis::args::multi_sampling(
								_vm
							),
							sge::renderer::pixel_format::srgb::no
						),
						sge::renderer::parameters::vsync::on,
						sanguis::args::display_mode(
							_vm
						)
					),
					sge::viewport::fill_on_resize()
				)
			)
			(
				sge::systems::input(
					sge::systems::cursor_option_field::null()
				)
			)
			(
				sge::systems::image2d(
					sge::image::capabilities_field{
						sge::image::capabilities::threadsafe
					},
					sge::media::optional_extension_set(
						sge::media::extension_set{
							sge::media::extension(
								FCPPT_TEXT("png")
							)
						}
					)
				)
			)
			(
				sge::systems::audio_loader(
					sge::audio::loader_capabilities_field::null(),
					sge::media::optional_extension_set(
						sge::media::extension_set{
							sge::media::extension(
								FCPPT_TEXT("ogg")
							)
						}
					)
				)
			)
			(
				sge::systems::audio_player_default()
			)
			// TODO: make sure that we can load truetype fonts, use a multi loader here as well!
		);
}
