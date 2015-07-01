#include <sanguis/client/gui/perk/make_tabs.hpp>
#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::client::gui::perk::state::state(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::gui::context &_context,
	sge::gui::style::base const &_style,
	sanguis::client::perk::state &_state
)
:
	tabs_(
		sanguis::client::gui::perk::make_tabs(
			_renderer,
			_font,
			_context,
			_style,
			_state
		)
	),
	main_tab_(
		_context,
		_style,
		_renderer,
		_font,
		fcppt::algorithm::map<
			sge::gui::widget::reference_name_vector
		>(
			tabs_,
			[](
				sanguis::client::gui::perk::tab_unique_ptr const &_tab
			)
			{
				return
					sge::gui::widget::reference_name_pair(
						sge::gui::widget::reference(
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

sge::gui::widget::tab &
sanguis::client::gui::perk::state::widget()
{
	return
		main_tab_;
}
