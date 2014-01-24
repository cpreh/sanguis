#include <sanguis/gui/viewport_adaptor.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/viewport/manager_fwd.hpp>


sanguis::gui::viewport_adaptor::viewport_adaptor(
	sge::renderer::device::core &_device,
	sge::viewport::manager &_viewport_manager,
	sge::rucksack::widget::base &_widget
)
:
	impl_(
		_viewport_manager,
		_device
	)
{
	impl_.child(
		_widget
	);

	impl_.relayout();
}

sanguis::gui::viewport_adaptor::~viewport_adaptor()
{
}
