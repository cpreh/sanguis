#include <sanguis/client/gui/perk/item_color.hpp>
#include <sanguis/client/gui/perk/line.hpp>
#include <sanguis/client/gui/perk/make_description.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level_callback.hpp>
#include <sanguis/client/perk/state.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/perk/state_ref.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::gui::perk::line::line(
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::gui::context_ref const _context,
    sge::gui::style::const_reference const _style,
    sanguis::client::perk::state_ref const _state,
    sanguis::client::perk::info const &_info)
    : perk_type_(_info.perk_type()),
      state_(_state),
      button_(
          _style,
          _renderer,
          _font,
          sge::font::from_fcppt_string(sanguis::client::perk::to_string(_info.perk_type())),
          sge::gui::optional_needed_width()),
      text_(
          _style,
          _renderer,
          _font,
          sanguis::client::gui::perk::make_description(_info),
          this->text_color(),
          sge::gui::optional_needed_width()),
      box_(
          _context,
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(button_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(text_), sge::rucksack::alignment::center)},
          sge::rucksack::axis::x),
      click_connection_(button_.click(sge::gui::click_callback{[this] { this->on_click(); }})),
      level_change_connection_(state_->register_level_change(
          sanguis::client::perk::level_callback{[this] { this->on_level_change(); }}))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::gui::perk::line::~line() = default;

sge::gui::widget::box_container &sanguis::client::gui::perk::line::widget() { return box_; }

void sanguis::client::gui::perk::line::on_click()
{
  if (state_->choose_perk(this->perk_type_))
  {
    fcppt::optional::maybe_void(
        sanguis::client::perk::find_info_const(
            this->perk_type_, fcppt::make_cref(this->state_->perks()))
            .value(),
        [this](sanguis::client::perk::info const &_info)
        { this->text_.value(sanguis::client::gui::perk::make_description(_info)); });
  }
}

void sanguis::client::gui::perk::line::on_level_change() { text_.text_color(this->text_color()); }

sge::gui::text_color sanguis::client::gui::perk::line::text_color() const
{
  return sanguis::client::gui::perk::item_color(sanguis::client::perk::choosable(
      perk_type_, state_->perks(), state_->player_level(), state_->remaining_levels()));
}
