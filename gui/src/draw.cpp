#include <sanguis/gui/draw.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


void
sanguis::gui::draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sanguis::gui::background::base &_background,
	sanguis::gui::main_area::base &_main_area
)
{
	_background.draw(
		_renderer,
		_context
	);

	_main_area.widget().on_draw(
		_renderer,
		_context
	);
}
