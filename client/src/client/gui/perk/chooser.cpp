#include <sanguis/duration.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/client/perk/change_callback.hpp>
#include <sanguis/client/perk/level_callback.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/gravity.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace
{

sge::rucksack::alignment const state_alignment(sge::rucksack::alignment::left_or_top);

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::gui::perk::chooser::chooser(
    sanguis::client::perk::state_ref const _state,
    sge::gui::style::const_reference const _style,
    sge::renderer::device::ffp_ref const _renderer,
    sge::viewport::manager_ref const _viewport_manager,
    sge::font::object_ref const _font)
    : state_(_state),
      style_(_style),
      renderer_(_renderer),
      font_(_font),
      gui_context_(),
      top_text_(
          _style,
          _renderer,
          _font,
          this->make_top_text(),
          sanguis::client::gui::default_text_color(),
          sge::gui::optional_needed_width()),
      gui_state_(fcppt::make_unique_ptr<sanguis::client::gui::perk::state>(
          _renderer, _font, fcppt::make_ref(gui_context_), _style, _state)),
      main_container_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(top_text_), sge::rucksack::alignment::left_or_top),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(gui_state_->widget()), state_alignment)},
          sge::rucksack::axis::y),
      gui_area_(
          fcppt::reference_to_base<sge::renderer::device::core>(_renderer),
          _viewport_manager,
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference{main_container_},
          sge::gui::gravity::north_east),
      gui_master_(fcppt::make_ref(gui_context_), sge::gui::main_area::reference{gui_area_}),
      gui_background_(sge::gui::main_area::reference{gui_area_}),
      perk_connection_(_state->register_perks_change(
          sanguis::client::perk::change_callback{[this] { this->perks(); }})),
      level_connection_(_state->register_level_change(
          sanguis::client::perk::level_callback{[this] { this->level(); }}))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::gui::perk::chooser::~chooser() = default;

void sanguis::client::gui::perk::chooser::process(sanguis::duration const &_delta)
{
  gui_master_.update(sanguis::client::gui::to_duration(_delta));
}

void sanguis::client::gui::perk::chooser::draw(sge::renderer::context::ffp &_context)
{
  gui_master_.draw_with_states(renderer_.get(), _context, gui_background_);
}

void sanguis::client::gui::perk::chooser::input(sge::input::event_base const &_event)
{
  gui_master_.process_event(_event);
}

void sanguis::client::gui::perk::chooser::perks()
{
  main_container_.pop_back();

  gui_state_ = fcppt::make_unique_ptr<sanguis::client::gui::perk::state>(
      renderer_, font_, fcppt::make_ref(gui_context_), style_, state_);

  main_container_.push_back(sge::gui::widget::reference_alignment_pair(
      sge::gui::widget::reference(gui_state_->widget()), state_alignment));

  gui_area_.relayout();
}

void sanguis::client::gui::perk::chooser::level() { top_text_.value(this->make_top_text()); }

sge::font::string sanguis::client::gui::perk::chooser::make_top_text() const
{
  return sge::font::from_fcppt_string(
      FCPPT_TEXT("Level: ") + fcppt::output_to_fcppt_string(state_->player_level()) +
      FCPPT_TEXT(", Perks to choose: ") +
      fcppt::output_to_fcppt_string(state_->remaining_levels()));
}
