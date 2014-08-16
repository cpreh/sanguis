#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


sanguis::gui::widget::dummy::dummy()
:
	sanguis::gui::widget::base()
{
}

sanguis::gui::widget::dummy::~dummy()
{
}

void
sanguis::gui::widget::dummy::on_draw(
	sanguis::gui::renderer::base &,
	sge::renderer::context::ffp &
)
{
}
