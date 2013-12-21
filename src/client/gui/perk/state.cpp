#include <sanguis/client/gui/perk/make_tabs.hpp>
#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_name_pair.hpp>
#include <sanguis/gui/widget/reference_name_vector.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::client::gui::perk::state::state(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::context &_context,
	sanguis::client::perk::state const &_state
)
:
	tabs_(
		sanguis::client::gui::perk::make_tabs(
			_renderer,
			_font,
			_context,
			_state
		)
	),
	main_tab_(
		_renderer,
		_font,
		_context,
		fcppt::algorithm::map<
			sanguis::gui::widget::reference_name_vector
		>(
			tabs_,
			[](
				sanguis::client::gui::perk::tab_unique_ptr const &_tab
			)
			{
				return
					sanguis::gui::widget::reference_name_pair(
						sanguis::gui::widget::reference(
							_tab->widget()
						),
						_tab->name()
					);
			}
		)
	)
{
}

sanguis::client::gui::perk::state::~state()
{
}

sanguis::gui::widget::tab &
sanguis::client::gui::perk::state::widget()
{
	return
		main_tab_;
}
