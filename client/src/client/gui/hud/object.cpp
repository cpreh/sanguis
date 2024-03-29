#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/health_value.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/max_health_valid.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/hud/object.hpp>
#include <sanguis/client/gui/hud/weapon_details.hpp>
#include <sanguis/client/gui/hud/weapon_widget.hpp>
#include <sanguis/client/load/hud/context_ref.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/gravity.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/bar.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/strong_typedef_arithmetic.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/div.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::gui::hud::object::object(
    sanguis::client::load::hud::context_ref const _resources,
    sge::gui::style::const_reference const _gui_style,
    sge::font::object_ref const _font,
    sge::renderer::device::ffp_ref const _renderer,
    sge::viewport::manager_ref const _viewport_manager)
    : reload_clock_(),
      resources_(_resources),
      gui_style_(_gui_style),
      font_(_font),
      renderer_(_renderer),
      exp_(0U),
      previous_exp_level_(0U),
      exp_for_next_level_(0U),
      frames_counter_(),
      gui_context_(),
      world_name_text_(
          _gui_style,
          _renderer,
          _font,
          sge::font::string(),
          sanguis::client::gui::default_text_color(),
          sge::gui::optional_needed_width()),
      player_name_text_(
          _gui_style,
          _renderer,
          _font,
          sge::font::string(),
          sanguis::client::gui::default_text_color(),
          sge::gui::optional_needed_width()),
      name_level_gap_(sge::rucksack::axis::x),
      level_text_(
          _gui_style,
          _renderer,
          _font,
          sge::font::string(),
          sanguis::client::gui::default_text_color(),
          sge::gui::optional_needed_width()),
      text_container_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(player_name_text_),
                  sge::rucksack::alignment::left_or_top),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(name_level_gap_),
                  sge::rucksack::alignment::left_or_top),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(level_text_), sge::rucksack::alignment::left_or_top)},
          sge::rucksack::axis::x),
      exp_bar_(
          _gui_style,
          sge::rucksack::dim(
              200, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          sge::rucksack::axis::x,
          sge::gui::fill_color(
              sge::image::color::any::object{sge::image::color::predef::forestgreen()}),
          sge::gui::fill_level(0.F)),
      health_bar_(
          _gui_style,
          sge::rucksack::dim(
              200, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          sge::rucksack::axis::x,
          sge::gui::fill_color(sge::image::color::any::object{sge::image::color::predef::red()}),
          sge::gui::fill_level(1.F)),
      middle_container_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(world_name_text_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(text_container_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(health_bar_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(exp_bar_), sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      middle_frame_(_gui_style, sge::gui::widget::reference{middle_container_}),
      primary_dummy_widget_h_(sge::rucksack::dim{
          0,
          84 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }),
      primary_weapon_(),
      primary_weapon_container_inner_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{sge::gui::widget::reference_alignment_pair(
              sge::gui::widget::reference(primary_dummy_widget_h_),
              sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      primary_dummy_widget_w_(sge::rucksack::dim{
          150, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          0}),
      primary_weapon_container_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(primary_dummy_widget_w_),
                  sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(primary_weapon_container_inner_),
                  sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      primary_weapon_frame_(_gui_style, sge::gui::widget::reference{primary_weapon_container_}),
      secondary_dummy_widget_h_(sge::rucksack::dim{
          0,
          84 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }),
      secondary_weapon_(),
      secondary_weapon_container_inner_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{sge::gui::widget::reference_alignment_pair(
              sge::gui::widget::reference(secondary_dummy_widget_h_),
              sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      secondary_dummy_widget_w_(sge::rucksack::dim{
          150, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          0}),
      secondary_weapon_container_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(secondary_dummy_widget_w_),
                  sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(secondary_weapon_container_inner_),
                  sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      secondary_weapon_frame_(_gui_style, sge::gui::widget::reference{secondary_weapon_container_}),
      main_widget_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(primary_weapon_frame_),
                  sge::rucksack::alignment::left_or_top),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(middle_frame_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(secondary_weapon_frame_),
                  sge::rucksack::alignment::left_or_top)},
          sge::rucksack::axis::x),
      gui_area_(
          fcppt::reference_to_base<sge::renderer::device::core>(_renderer),
          _viewport_manager,
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference{main_widget_},
          sge::gui::gravity::north_west),
      gui_master_(fcppt::make_ref(gui_context_), sge::gui::main_area::reference{gui_area_}),
      gui_background_(sge::gui::main_area::reference{gui_area_}),
      weapon_details_(),
      paused_{false}
{
}

sanguis::client::gui::hud::object::~object() = default;

void sanguis::client::gui::hud::object::health_pair(
    sanguis::client::optional_health_pair const &_opt_health_pair)
{
  health_bar_.value(fcppt::optional::maybe(
      fcppt::optional::bind(
          _opt_health_pair,
          [](sanguis::client::health_pair const &_health_pair)
          {
            return fcppt::optional::join(fcppt::optional::make_if(
                sanguis::client::max_health_valid(_health_pair.max_health()),
                [&_health_pair] {
                  return fcppt::math::div(
                      _health_pair.health().get(), _health_pair.max_health().get());
                }));
          }),
      fcppt::const_(sge::gui::fill_level(0.F)),
      [](sanguis::client::health_value const _health)
      {
        return fcppt::strong_typedef_construct_cast<sge::gui::fill_level, fcppt::cast::size_fun>(
            _health);
      }));
}

void sanguis::client::gui::hud::object::experience(sanguis::client::exp const _exp)
{
  exp_ = _exp;

  this->update_exp();
}

void sanguis::client::gui::hud::object::level(
    sanguis::client::level const _level,
    sanguis::client::exp_for_next_level const _exp_for_next_level)
{
  level_text_.value(SGE_FONT_LIT("Level: ") + fcppt::output_to_string<sge::font::string>(_level));

  previous_exp_level_ = exp_for_next_level_;

  exp_for_next_level_ = _exp_for_next_level;

  this->update_exp();
}

void sanguis::client::gui::hud::object::add_weapon(sanguis::weapon_description const &_description)
{
  this->update_weapon_widgets(
      [&_description, this]
      {
        this->weapon_widget(sanguis::weapon_type_to_is_primary(_description.weapon_type())) =
            optional_weapon_widget_unique_ptr(
                fcppt::make_unique_ptr<sanguis::client::gui::hud::weapon_widget>(
                    fcppt::make_cref(reload_clock_),
                    resources_,
                    fcppt::make_ref(gui_context_),
                    gui_style_,
                    renderer_,
                    font_,
                    _description));
      });
}

void sanguis::client::gui::hud::object::remove_weapon(sanguis::is_primary_weapon const _is_primary)
{
  this->update_weapon_widgets(
      [_is_primary, this]
      { this->weapon_widget(_is_primary) = optional_weapon_widget_unique_ptr(); });
}

void sanguis::client::gui::hud::object::magazine_remaining(
    sanguis::is_primary_weapon const _is_primary,
    sanguis::magazine_remaining const _magazine_remaining)
{
  this->weapon_widget_checked(_is_primary).magazine_remaining(_magazine_remaining);
}

void sanguis::client::gui::hud::object::reload_time(
    sanguis::is_primary_weapon const _is_primary, sanguis::duration const _reload_time)
{
  this->weapon_widget_checked(_is_primary).reload_time(_reload_time);
}

void sanguis::client::gui::hud::object::world_name(sanguis::world_name const &_name)
{
  world_name_text_.value(sge::font::from_fcppt_string(_name.get()));
}

void sanguis::client::gui::hud::object::player_name(sanguis::player_name const &_name)
{
  player_name_text_.value(sge::font::from_fcppt_string(_name.get()));
}

void sanguis::client::gui::hud::object::update(sanguis::duration const _duration)
{
  gui_master_.update(sanguis::client::gui::to_duration(_duration));

  this->foreach_weapon([](sanguis::client::gui::hud::weapon_widget &_widget) { _widget.update(); });
}

void sanguis::client::gui::hud::object::update_server(
    sanguis::client::slowed_duration const _duration)
{
  if (!paused_)
  {
    reload_clock_.update(
        std::chrono::duration_cast<sanguis::diff_clock::duration>(_duration.get()));
  }
}

void sanguis::client::gui::hud::object::pause(bool const _paused) { paused_ = _paused; }

void sanguis::client::gui::hud::object::draw(sge::renderer::context::ffp &_render_context)
{
  frames_counter_.update();

  gui_master_.draw_with_states(renderer_.get(), _render_context, gui_background_);
}

void sanguis::client::gui::hud::object::details(bool const _show)
{
  if (_show)
  {
    this->create_details();
  }
  else if (weapon_details_.has_value())
  {
    this->destroy_details();
  }

  gui_area_.relayout();
}

sanguis::client::gui::hud::object::optional_weapon_widget_unique_ptr &
sanguis::client::gui::hud::object::weapon_widget(sanguis::is_primary_weapon const _is_primary)
{
  return _is_primary.get() ? primary_weapon_ : secondary_weapon_;
}

sanguis::client::gui::hud::weapon_widget &sanguis::client::gui::hud::object::weapon_widget_checked(
    sanguis::is_primary_weapon const _is_primary)
{
  return *fcppt::optional::to_exception(
      this->weapon_widget(_is_primary),
      [] { return sanguis::exception{FCPPT_TEXT("Weapon widget not set!")}; });
}

template <typename Function>
void sanguis::client::gui::hud::object::update_weapon_widgets(Function const &_function)
{
  primary_weapon_container_inner_.clear();
  primary_weapon_container_inner_.push_back(sge::gui::widget::reference_alignment_pair{
      sge::gui::widget::reference{primary_dummy_widget_h_}, sge::rucksack::alignment::center});
  secondary_weapon_container_inner_.clear();
  secondary_weapon_container_inner_.push_back(sge::gui::widget::reference_alignment_pair{
      sge::gui::widget::reference{secondary_dummy_widget_h_}, sge::rucksack::alignment::center});

  _function();

  this->foreach_weapon(
      [this](sanguis::client::gui::hud::weapon_widget &_widget)
      {
        if (sanguis::weapon_type_to_is_primary(_widget.weapon_description().weapon_type()).get())
        {
          primary_weapon_container_inner_.clear();
          primary_weapon_container_inner_.push_back(sge::gui::widget::reference_alignment_pair{
              sge::gui::widget::reference{_widget.widget()}, sge::rucksack::alignment::center});
        }
        else
        {
          secondary_weapon_container_inner_.clear();
          secondary_weapon_container_inner_.push_back(sge::gui::widget::reference_alignment_pair{
              sge::gui::widget::reference{_widget.widget()}, sge::rucksack::alignment::center});
        }
      });

  if (weapon_details_.has_value())
  {
    this->destroy_details();

    this->create_details();
  }

  gui_area_.relayout();
}

template <typename Function>
void sanguis::client::gui::hud::object::foreach_weapon(Function const &_function)
{
  auto const apply_maybe(
      [&_function](optional_weapon_widget_unique_ptr const &_widget)
      {
        fcppt::optional::maybe_void(
            _widget, [&_function](weapon_widget_unique_ptr const &_ptr) { _function(*_ptr); });
      });

  apply_maybe(primary_weapon_);

  apply_maybe(secondary_weapon_);
}

void sanguis::client::gui::hud::object::update_exp()
{
  sanguis::client::exp_for_next_level const diff(exp_for_next_level_ - previous_exp_level_);

  fcppt::optional::maybe_void(
      fcppt::math::div(
          fcppt::cast::int_to_float<sge::gui::fill_level::value_type>(
              exp_.get() - previous_exp_level_.get()),
          fcppt::cast::int_to_float<sge::gui::fill_level::value_type>(diff.get())),
      [this](sge::gui::fill_level::value_type const _level)
      { exp_bar_.value(sge::gui::fill_level{_level}); });
}

void sanguis::client::gui::hud::object::create_details()
{
  auto const maybe_description(
      [](optional_weapon_widget_unique_ptr const &_widget) -> sanguis::optional_weapon_description
      {
        return fcppt::optional::map(
            _widget,
            [](weapon_widget_unique_ptr const &_ptr) -> sanguis::weapon_description
            { return _ptr->weapon_description(); });
      });

  weapon_details_unique_ptr new_details(
      fcppt::make_unique_ptr<sanguis::client::gui::hud::weapon_details>(
          fcppt::make_ref(gui_context_),
          gui_style_,
          renderer_,
          font_,
          maybe_description(primary_weapon_),
          maybe_description(secondary_weapon_)));

  main_widget_.push_back(sge::gui::widget::reference_alignment_pair{
      sge::gui::widget::reference{new_details->widget()}, sge::rucksack::alignment::left_or_top});

  weapon_details_ = optional_weapon_details_unique_ptr(std::move(new_details));
}

void sanguis::client::gui::hud::object::destroy_details()
{
  main_widget_.pop_back();

  weapon_details_ = optional_weapon_details_unique_ptr();
}
