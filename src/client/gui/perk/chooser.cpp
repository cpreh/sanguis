#include <sanguis/duration.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::perk::chooser::chooser(
	sanguis::client::perk::state &_state,
	sge::renderer::device::ffp &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::font::object &_font,
	sge::input::cursor::object &_cursor,
	sge::input::keyboard::device &_keyboard
)
:
	state_(
		_state
	),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	gui_context_(),
	top_text_(
		_renderer,
		_font,
		// TODO: Initialize!
		SGE_FONT_LIT("")
	),
	gui_state_(
		fcppt::make_unique_ptr<
			sanguis::client::gui::perk::state
		>(
			_renderer,
			_font,
			gui_context_,
			_state
		)
	),
	main_container_(
		gui_context_,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					top_text_
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					gui_state_->widget()
				),
				sge::rucksack::alignment::left_or_top
			)
		},
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	gui_master_(
		_renderer,
		_viewport_manager,
		_keyboard,
		_cursor,
		gui_context_,
		main_container_
	),
	perk_connection_(
		_state.register_perks_change(
			std::bind(
				&sanguis::client::gui::perk::chooser::perks,
				this
			)
		)
	),
	level_connection_(
		_state.register_level_change(
			std::bind(
				&sanguis::client::gui::perk::chooser::level,
				this
			)
		)
	)
{
	this->level();
}

sanguis::client::gui::perk::chooser::~chooser()
{
}

void
sanguis::client::gui::perk::chooser::process(
	sanguis::duration const &_delta
)
{
	gui_master_.update();
}

void
sanguis::client::gui::perk::chooser::draw(
	sge::renderer::context::ffp &_context
)
{
	gui_master_.draw(
		_context
	);
}

void
sanguis::client::gui::perk::chooser::perks()
{
	main_container_.pop_back();

	gui_state_.take(
		fcppt::make_unique_ptr<
			sanguis::client::gui::perk::state
		>(
			renderer_,
			font_,
			gui_context_,
			state_
		)
	);

	main_container_.push_back(
		sanguis::gui::widget::reference_alignment_pair(
			sanguis::gui::widget::reference(
				gui_state_->widget()
			),
			// TODO: Constant!
			sge::rucksack::alignment::left_or_top
		)
	);
}

void
sanguis::client::gui::perk::chooser::level()
{
	this->update_top_text();
}

void
sanguis::client::gui::perk::chooser::update_top_text()
{
	top_text_.value(
		sge::font::from_fcppt_string(
			FCPPT_TEXT("Level: ")
			+
			fcppt::insert_to_fcppt_string(
				state_.player_level()
			)
			+
			FCPPT_TEXT(", Perks to choose: ")
			+
			fcppt::insert_to_fcppt_string(
				state_.remaining_levels()
			)
		)
	);
}
