#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/background/colored.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>


sanguis::gui::background::colored::colored(
	sge::renderer::device::ffp &_renderer,
	sanguis::gui::main_area::base &_main_area
)
:
	sanguis::gui::background::base(
		_main_area
	),
	renderer_(
		_renderer
	)
{
}

sanguis::gui::background::colored::~colored()
{
}

void
sanguis::gui::background::colored::on_draw(
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
)
{
	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		_area,
		sge::image::color::any::object(
			sge::image::color::rgba8(
				(sge::image::color::init::red() %= .75)
				(sge::image::color::init::green() %= .75)
				(sge::image::color::init::blue() %= .75)
				(sge::image::color::init::alpha() %= .25)
			)
		)
	);
}
