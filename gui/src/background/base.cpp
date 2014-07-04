#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::background::base::base(
	sanguis::gui::main_area::base &_main_area
)
:
	main_area_(
		_main_area
	)
{
}

sanguis::gui::background::base::~base()
{
}

void
sanguis::gui::background::base::draw(
	sge::renderer::context::ffp &_context
)
{
	this->on_draw(
		_context,
		this->widget().layout().area()
	);
}

sanguis::gui::widget::base &
sanguis::gui::background::base::widget()
{
	return
		main_area_.widget();
}
