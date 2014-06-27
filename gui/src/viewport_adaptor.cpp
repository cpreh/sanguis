#include <sanguis/gui/viewport_adaptor.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/viewport/manager_fwd.hpp>


sanguis::gui::viewport_adaptor::viewport_adaptor(
	sge::renderer::device::core &_device,
	sge::viewport::manager &_viewport_manager,
	sanguis::gui::widget::base &_widget
)
:
	widget_(
		_widget
	),
	impl_(
		_viewport_manager,
		_device
	)
{
	impl_.child(
		_widget.layout()
	);

	impl_.relayout();
}

sanguis::gui::viewport_adaptor::~viewport_adaptor()
{
}

void
sanguis::gui::viewport_adaptor::relayout()
{
	impl_.relayout();
}

sanguis::gui::widget::base &
sanguis::gui::viewport_adaptor::widget()
{
	return
		widget_;
}
