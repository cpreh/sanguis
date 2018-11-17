#include <sanguis/duration.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/client/perk/change_callback.hpp>
#include <sanguis/client/perk/level_callback.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/gravity.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::rucksack::alignment const state_alignment(
	sge::rucksack::alignment::left_or_top
);

}

sanguis::client::gui::perk::chooser::chooser(
	sanguis::client::perk::state &_state,
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::font::object &_font
)
:
	state_(
		_state
	),
	style_(
		_style
	),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	gui_context_(),
	top_text_(
		_style,
		_renderer,
		_font,
		this->make_top_text(),
		sanguis::client::gui::default_text_color(),
		sge::gui::optional_needed_width()
	),
	gui_state_(
		fcppt::make_unique_ptr<
			sanguis::client::gui::perk::state
		>(
			_renderer,
			_font,
			gui_context_,
			_style,
			_state
		)
	),
	main_container_(
		gui_context_,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					top_text_
				),
				sge::rucksack::alignment::left_or_top
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					gui_state_->widget()
				),
				state_alignment
			)
		},
		sge::rucksack::axis::y
	),
	gui_area_(
		_renderer,
		_viewport_manager,
		gui_context_,
		main_container_,
		sge::gui::gravity::north_east
	),
	gui_master_(
		gui_context_,
		gui_area_
	),
	gui_background_(
		gui_area_
	),
	perk_connection_(
		_state.register_perks_change(
			sanguis::client::perk::change_callback{
				std::bind(
					&sanguis::client::gui::perk::chooser::perks,
					this
				)
			}
		)
	),
	level_connection_(
		_state.register_level_change(
			sanguis::client::perk::level_callback{
				std::bind(
					&sanguis::client::gui::perk::chooser::level,
					this
				)
			}
		)
	)
{
}

sanguis::client::gui::perk::chooser::~chooser()
{
}

void
sanguis::client::gui::perk::chooser::process(
	sanguis::duration const &_delta
)
{
	gui_master_.update(
		sanguis::client::gui::to_duration(
			_delta
		)
	);
}

void
sanguis::client::gui::perk::chooser::draw(
	sge::renderer::context::ffp &_context
)
{
	gui_master_.draw_with_states(
		renderer_,
		_context,
		gui_background_
	);
}

void
sanguis::client::gui::perk::chooser::input(
	sge::input::event_base const &_event
)
{
	gui_master_.process_event(
		_event
	);
}

void
sanguis::client::gui::perk::chooser::perks()
{
	main_container_.pop_back();

	gui_state_ =
		fcppt::make_unique_ptr<
			sanguis::client::gui::perk::state
		>(
			renderer_,
			font_,
			gui_context_,
			style_,
			state_
		);

	main_container_.push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				gui_state_->widget()
			),
			state_alignment
		)
	);

	gui_area_.relayout();
}

void
sanguis::client::gui::perk::chooser::level()
{
	top_text_.value(
		this->make_top_text()
	);
}

sge::font::string
sanguis::client::gui::perk::chooser::make_top_text() const
{
	return
		sge::font::from_fcppt_string(
			FCPPT_TEXT("Level: ")
			+
			fcppt::output_to_fcppt_string(
				state_.player_level()
			)
			+
			FCPPT_TEXT(", Perks to choose: ")
			+
			fcppt::output_to_fcppt_string(
				state_.remaining_levels()
			)
		);
}
