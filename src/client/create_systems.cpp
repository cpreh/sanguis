#include <sanguis/app_name.hpp>
#include <sanguis/args/display_mode.hpp>
#include <sanguis/args/multi_sampling.hpp>
#include <sanguis/client/create_systems.hpp>
#include <sanguis/client/systems.hpp>
#include <sanguis/client/systems_unique_ptr.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/title.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
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
					sge::image::capabilities_field(
						sge::image::capabilities::threadsafe
					),
					sge::media::optional_extension_set(
						fcppt::assign::make_container<
							sge::media::extension_set
						>(
							sge::media::extension(
								FCPPT_TEXT("png")
							)
						)
					)
				)
			)
			// TODO: make sure that we can load truetype fonts, use a multi loader here as well!
		);
}
