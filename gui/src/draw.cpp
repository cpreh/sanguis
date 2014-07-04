#include <sanguis/gui/draw.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


void
sanguis::gui::draw(
	sge::renderer::context::ffp &_context,
	sanguis::gui::background::base &_background,
	sanguis::gui::main_area::base &_main_area
)
{
	_background.draw(
		_context
	);

	_main_area.widget().on_draw(
		_context
	);
}
