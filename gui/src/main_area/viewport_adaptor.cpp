#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/main_area/viewport_adaptor.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>


sanguis::gui::main_area::viewport_adaptor::viewport_adaptor(
	sge::renderer::device::core &_device,
	sge::viewport::manager &_viewport_manager,
	sanguis::gui::widget::base &_widget
)
:
	sanguis::gui::main_area::base(),
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

sanguis::gui::main_area::viewport_adaptor::~viewport_adaptor()
{
}

void
sanguis::gui::main_area::viewport_adaptor::relayout()
{
	impl_.relayout();
}

sanguis::gui::widget::base &
sanguis::gui::main_area::viewport_adaptor::widget()
{
	return
		widget_;
}
