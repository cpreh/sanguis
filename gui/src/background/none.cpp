#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/background/none.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/renderer/base.hpp>
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
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
)
{
}
