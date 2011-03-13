#include "client_sge_options.hpp"
#include "multi_sampling.hpp"
#include "screen_mode.hpp"
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/simple_parameters.hpp>
#include <sge/extension_set.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <awl/mainloop/io_service_shared_ptr.hpp>
#include <awl/mainloop/io_service.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::systems::list const
sanguis::args::client_sge_options(
	boost::program_options::variables_map const &_vm
)
{
	sge::window::dim const dimensions(
		1024,
		768
	);

	return
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sanguis"),
					dimensions
				)
			)
			.io_service(
				awl::mainloop::io_service_shared_ptr(
					awl::mainloop::asio::create_io_service_base()
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					args::screen_mode(
						_vm
					),
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::multi_sample_type(
						args::multi_sampling(
							_vm
						)
					)
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field::null()
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
