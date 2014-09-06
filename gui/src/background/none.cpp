#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/background/none.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>


sanguis::gui::background::none::none(
	sanguis::gui::main_area::base &_main_area
)
:
	sanguis::gui::background::base(
		_main_area
	)
{
}

sanguis::gui::background::none::~none()
{
}

void
sanguis::gui::background::none::on_draw(
	sanguis::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
)
{
}
