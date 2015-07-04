#include <sanguis/app_name.hpp>
#include <sanguis/company_name.hpp>
#include <sanguis/client/create_systems.hpp>
#include <sanguis/client/systems.hpp>
#include <sanguis/client/systems_unique_ptr.hpp>
#include <sanguis/client/args/display_mode.hpp>
#include <sanguis/client/args/multi_sampling.hpp>
#include <sanguis/client/args/sge_log_level.hpp>
#include <sge/config/log_path.hpp>
#include <sge/config/own_app_name.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/title.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::systems_unique_ptr
sanguis::client::create_systems(
	boost::program_options::variables_map const &_vm
)
{
	return
		fcppt::make_unique_ptr_fcppt<
			sanguis::client::systems
		>(
			sge::systems::make_list
			(
				sge::systems::config()
				.log_settings(
					sge::systems::log_settings(
						sge::log::option_container{
							sge::log::option{
								sge::log::location(),
								sanguis::client::args::sge_log_level(
									_vm
								)
							}
						}
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
					sge::systems::window_source(
						sge::systems::original_window(
							sge::window::title(
								sanguis::app_name()
							)
						)
						.hide_cursor()
					)
				)
			)
			(
				sge::systems::renderer(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::d24s8,
						sanguis::client::args::multi_sampling(
							_vm
						),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::display_mode::parameters(
						sge::renderer::display_mode::vsync::on,
						sanguis::client::args::display_mode(
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
		);
}
