#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/minimum_size_area.hpp>
#include <sanguis/gui/gravity.hpp>
#include <sanguis/gui/aux_/make_container_pair.hpp>
#include <sanguis/gui/aux_/gravity_east.hpp>
#include <sanguis/gui/aux_/gravity_south.hpp>
#include <sanguis/gui/aux_/swap_pair.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_fwd.hpp>


sanguis::gui::minimum_size_area::minimum_size_area(
	sge::renderer::device::core &_renderer,
	sge::viewport::manager &_viewport_manager,
	sanguis::gui::context &_gui_context,
	sanguis::gui::widget::base &_widget,
	sanguis::gui::gravity const _gravity
)
:
	widget_(
		_widget
	),
	minimum_size_(
		_widget
	),
	horizontal_expander_(
		sge::rucksack::axis::x
	),
	vertical_expander_(
		sge::rucksack::axis::y
	),
	horizontal_container_(
		_gui_context,
		sanguis::gui::aux_::make_container_pair(
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference(
					minimum_size_
				),
				sge::rucksack::alignment::center
			},
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference(
					horizontal_expander_
				),
				sge::rucksack::alignment::center
			},
			sanguis::gui::aux_::swap_pair{
				sanguis::gui::aux_::gravity_east(
					_gravity
				)
			}
		),
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	vertical_container_(
		_gui_context,
		sanguis::gui::aux_::make_container_pair(
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference(
					horizontal_container_
				),
				sge::rucksack::alignment::center
			},
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference(
					vertical_expander_
				),
				sge::rucksack::alignment::center
			},
			sanguis::gui::aux_::swap_pair{
				sanguis::gui::aux_::gravity_south(
					_gravity
				)
			}
		),
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	viewport_adaptor_(
		_renderer,
		_viewport_manager,
		vertical_container_
	)
{
}

sanguis::gui::minimum_size_area::~minimum_size_area()
{
}

void
sanguis::gui::minimum_size_area::relayout()
{
	viewport_adaptor_.relayout();
}

sanguis::gui::widget::base &
sanguis::gui::minimum_size_area::widget()
{
	return
		widget_;
}
