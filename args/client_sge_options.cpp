#include "client_sge_options.hpp"
#include "multi_sampling.hpp"
#include "resolution.hpp"
#include "window_mode.hpp"
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/window_parameters.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/window/parameters.hpp>
#include <sge/extension_set.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::systems::list const
sanguis::args::client_sge_options(
	boost::program_options::variables_map const &_vm
)
{
	return
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sanguis")
				)
			)
			.io_service(
				awl::mainloop::asio::create_io_service_base()
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						args::resolution(
							_vm
						),
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					),
					sge::renderer::depth_buffer::off,
					sge::renderer::stencil_buffer::off,
					args::window_mode(
						_vm
					),
					sge::renderer::vsync::on,
					sge::renderer::multi_sample_type(
						args::multi_sampling(
							_vm
						)
					)
				),
				sge::systems::viewport::manage_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_grab::off
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field(
					sge::image::capabilities::threadsafe
				),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
		(
			sge::systems::audio_loader(
				sge::audio::loader_capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("ogg")
				)
			)
		)
		(
			sge::systems::audio_player_default()
		)
		(
			sge::systems::parameterless::font // TODO: make sure that we can load truetype fonts, use a multi loader here as well!
		);
}
