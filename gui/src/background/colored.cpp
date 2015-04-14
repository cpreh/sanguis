#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/background/colored.hpp>
#include <sanguis/gui/impl/fill_rect.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>


sanguis::gui::background::colored::colored(
	sanguis::gui::main_area::base &_main_area
)
:
	sanguis::gui::background::base(
		_main_area
	)
{
}

sanguis::gui::background::colored::~colored()
{
}

void
sanguis::gui::background::colored::on_draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
)
{
	_renderer.fill_rect(
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
