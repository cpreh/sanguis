#include <sanguis/client/gui/perk/item_color.hpp>
#include <sanguis/client/gui/perk/line.hpp>
#include <sanguis/client/gui/perk/make_description.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/needed_width.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::perk::line::line(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::context &_context,
	sanguis::gui::style::base const &_style,
	sanguis::client::perk::state &_state,
	sanguis::client::perk::info const &_info
)
:
	perk_type_(
		_info.perk_type()
	),
	state_(
		_state
	),
	button_(
		_style,
		_renderer,
		_font,
		sge::font::from_fcppt_string(
			sanguis::client::perk::to_string(
				_info.perk_type()
			)
		),
		sanguis::gui::optional_needed_width()
	),
	text_(
		_style,
		_renderer,
		_font,
		sanguis::client::gui::perk::make_description(
			_info
		),
		this->text_color(),
		sanguis::gui::optional_needed_width(
			sanguis::gui::needed_width(
				400 // TODO!
			)
		)
	),
	box_(
		_context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					button_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					text_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	click_connection_(
		button_.click(
			std::bind(
				&sanguis::client::gui::perk::line::on_click,
				this
			)
		)
	),
	level_change_connection_(
		state_.register_level_change(
			std::bind(
				&sanguis::client::gui::perk::line::on_level_change,
				this
			)
		)
	)
{
}

sanguis::client::gui::perk::line::~line()
{
}

sanguis::gui::widget::box_container &
sanguis::client::gui::perk::line::widget()
{
	return
		box_;
}

void
sanguis::client::gui::perk::line::on_click()
{
	if(
		state_.choose_perk(
			perk_type_
		)
	)
		text_.value(
			sanguis::client::gui::perk::make_description(
				*sanguis::client::perk::find_info_const(
					perk_type_,
					state_.perks()
				).value()
			)
		);
}

void
sanguis::client::gui::perk::line::on_level_change()
{
	text_.text_color(
		this->text_color()
	);
}

sanguis::gui::text_color
sanguis::client::gui::perk::line::text_color() const
{
	return
		sanguis::client::gui::perk::item_color(
			sanguis::client::perk::choosable(
				perk_type_,
				state_.perks(),
				state_.player_level(),
				state_.remaining_levels()
			)
		);
}
