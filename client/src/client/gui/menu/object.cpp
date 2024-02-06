#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/client/config/settings/object.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/config/settings/object_ref.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/font/to_std_wstring.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/needed_width_from_strings.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/text_callback.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/get_or_create.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/set_or_create.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/const.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/narrow.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::parse::ini::section_name const config_section(std::string{"gui_menu"});

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::parse::ini::entry_name const config_hostname_key(std::string{"hostname"});

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::parse::ini::entry_name const config_port_key(std::string{"port"});

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::parse::ini::entry_name const config_quickstart_port_key(std::string{"quickstartport"});

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::parse::ini::entry_name const config_player_name_key(std::string{"playername"});

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::font::string const connect_text(SGE_FONT_LIT("Connect"));

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::font::string const cancel_text(SGE_FONT_LIT("Cancel"));

FCPPT_PP_POP_WARNING

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::gui::menu::object::object(
    sge::renderer::device::ffp_ref const _renderer,
    sge::viewport::manager_ref const _viewport_manager,
    sge::font::object_ref const _font,
    sanguis::client::config::settings::object_ref const _settings,
    sanguis::client::gui::menu::callbacks::object &&_callbacks,
    sge::gui::style::const_reference const _gui_style)
    : settings_(_settings),
      renderer_(_renderer),
      gui_context_(),
      callbacks_(std::move(_callbacks)),
      quickstart_button_(
          _gui_style,
          _renderer,
          _font,
          SGE_FONT_LIT("Quickstart"),
          sge::gui::optional_needed_width()),
      resolution_chooser_(fcppt::make_ref(gui_context_), _gui_style, _font, _renderer),
      player_name_label_(
          _gui_style,
          _renderer,
          _font,
          SGE_FONT_LIT("Name: "),
          sanguis::client::gui::default_text_color()),
      player_name_edit_(
          _gui_style,
          _renderer,
          _font,
          sge::font::from_fcppt_string(
              fcppt::from_std_string(sge::parse::ini::get_or_create(
                                         fcppt::make_ref(_settings->sections()),
                                         config_section,
                                         config_player_name_key,
                                         sge::parse::ini::value(std::string{}))
                                         .get()))),
      player_name_line_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(player_name_label_),
                  sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(player_name_edit_),
                  sge::rucksack::alignment::center)},
          sge::rucksack::axis::x),
      hostname_label_(
          _gui_style,
          _renderer,
          _font,
          SGE_FONT_LIT("Hostname: "),
          sanguis::client::gui::default_text_color()),
      hostname_edit_(
          _gui_style,
          _renderer,
          _font,
          sge::font::from_fcppt_string(
              fcppt::from_std_string(sge::parse::ini::get_or_create(
                                         fcppt::make_ref(_settings->sections()),
                                         config_section,
                                         config_hostname_key,
                                         sge::parse::ini::value(std::string{}))
                                         .get()))),
      hostname_line_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(hostname_label_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(hostname_edit_), sge::rucksack::alignment::center)},
          sge::rucksack::axis::x),
      port_label_(
          _gui_style,
          _renderer,
          _font,
          SGE_FONT_LIT("Port: "),
          sanguis::client::gui::default_text_color()),
      port_edit_(
          _gui_style,
          _renderer,
          _font,
          sge::font::from_fcppt_string(
              fcppt::from_std_string(sge::parse::ini::get_or_create(
                                         fcppt::make_ref(_settings->sections()),
                                         config_section,
                                         config_port_key,
                                         sge::parse::ini::value(std::string{}))
                                         .get()))),
      port_line_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(port_label_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(port_edit_), sge::rucksack::alignment::center)},
          sge::rucksack::axis::x),
      connect_text_(
          _gui_style,
          _renderer,
          _font,
          SGE_FONT_LIT(""),
          sanguis::client::gui::default_text_color(),
          sge::gui::optional_needed_width()),
      connect_button_(
          _gui_style,
          _renderer,
          _font,
          connect_text,
          sge::gui::optional_needed_width(sge::gui::needed_width_from_strings(
              _font.get(), sge::gui::string_container{connect_text, cancel_text}))),
      connect_box_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(hostname_line_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(port_line_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(connect_text_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(connect_button_), sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      connect_frame_(_gui_style, sge::gui::widget::reference{connect_box_}),
      quit_button_(
          _gui_style, _renderer, _font, SGE_FONT_LIT("Quit"), sge::gui::optional_needed_width()),
      main_container_(
          fcppt::make_ref(gui_context_),
          sge::gui::widget::reference_alignment_vector{
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(quickstart_button_),
                  sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(resolution_chooser_.widget()),
                  sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(player_name_line_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(connect_frame_), sge::rucksack::alignment::center),
              sge::gui::widget::reference_alignment_pair(
                  sge::gui::widget::reference(quit_button_), sge::rucksack::alignment::center)},
          sge::rucksack::axis::y),
      gui_area_(
          fcppt::reference_to_base<sge::renderer::device::core>(_renderer),
          _viewport_manager,
          sge::gui::widget::reference{main_container_}),
      gui_master_(fcppt::make_ref(gui_context_), sge::gui::main_area::reference{gui_area_}),
      gui_background_(sge::gui::main_area::reference{gui_area_}),
      connect_running_{false},
      quickstart_connection_(quickstart_button_.click(
          sge::gui::click_callback{[this] { this->handle_quickstart(); }})),
      connect_connection_(
          connect_button_.click(sge::gui::click_callback{[this] { this->handle_connect(); }})),
      quit_connection_(quit_button_.click(sge::gui::click_callback{callbacks_.quit()})),
      hostname_change_connection_(hostname_edit_.text_change(sge::gui::text_callback{
          [this](sge::font::string const &) { this->handle_text_changed(); }})),
      port_change_connection_(port_edit_.text_change(sge::gui::text_callback{
          [this](sge::font::string const &) { this->handle_text_changed(); }}))
{
  this->handle_text_changed();
}

FCPPT_PP_POP_WARNING

sanguis::client::gui::menu::object::~object()
{
  auto const save_setting(
      [this](sge::parse::ini::entry_name const &_entry, sge::font::string const &_value)
      {
        // FIXME
        fcppt::optional::maybe_void(
            fcppt::optional::bind(
                sge::font::to_fcppt_string(_value),
                [](fcppt::string const &_inner) { return fcppt::to_std_string(_inner); }),
            [this, &_entry](std::string const &_string)
            {
              sge::parse::ini::set_or_create(
                  fcppt::make_ref(this->settings_->sections()),
                  config_section,
                  _entry,
                  sge::parse::ini::value(_string));
            });
      });

  save_setting(config_port_key, port_edit_.text());

  save_setting(config_hostname_key, hostname_edit_.text());

  save_setting(config_player_name_key, player_name_edit_.text());
}

void sanguis::client::gui::menu::object::process(sanguis::duration const &_delta)
{
  gui_master_.update(sanguis::client::gui::to_duration(_delta));
}

void sanguis::client::gui::menu::object::draw(sge::renderer::context::ffp &_render_context)
{
  _render_context.clear(sge::renderer::clear::parameters().back_buffer(
      sge::image::color::any::object{sge::image::color::predef::black()}));

  gui_master_.draw_with_states(renderer_.get(), _render_context, gui_background_);
}

void sanguis::client::gui::menu::object::connection_error(fcppt::string const &_message)
{
  connect_text_.value(sge::font::from_fcppt_string(_message));

  connect_button_.text(connect_text);

  connect_running_ = false;
}

void sanguis::client::gui::menu::object::input(sge::input::event_base const &_event)
{
  gui_master_.process_event(_event);
}

fcppt::string sanguis::client::gui::menu::object::player_name() const
{
  return
      // FIXME
      fcppt::optional::to_exception(
          sge::font::to_fcppt_string(player_name_edit_.text()),
          [] { return fcppt::exception{FCPPT_TEXT("Invalid player name!")}; });
}

void sanguis::client::gui::menu::object::handle_quickstart()
{
  if (connect_running_)
  {
    return;
  }

  connect_running_ = true;

  callbacks_.quickstart()(alda::net::port(fcppt::optional::to_exception(
      fcppt::extract_from_string<alda::net::port::value_type>(
          // TODO(philipp): Use server port here if it was specified
          sge::parse::ini::get_or_create(
              fcppt::make_ref(settings_->sections()),
              config_section,
              config_quickstart_port_key,
              sge::parse::ini::value("31337"))
              .get()),
      [] { return sanguis::exception{FCPPT_TEXT("Invalid port in ini file")}; })));
}

void sanguis::client::gui::menu::object::handle_text_changed()
{
  using port_type = std::uint64_t;

  connect_button_.enable(fcppt::optional::maybe(
      fcppt::extract_from_string<port_type>(port_edit_.text()),
      fcppt::const_(false),
      [this](port_type const _port)
      {
        return !hostname_edit_.text().empty() && _port > 0 &&
               _port <
                   65535; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }));
}

void sanguis::client::gui::menu::object::handle_connect()
{
  if (!connect_running_)
  {
    callbacks_.connect()(
        alda::net::host(fcppt::optional::to_exception(
            // FIXME
            fcppt::narrow(sge::font::to_std_wstring(hostname_edit_.text())),
            [] { return sanguis::exception{FCPPT_TEXT("Invalid host name")}; })),
        alda::net::port(fcppt::optional::to_exception(
            // FIXME
            fcppt::extract_from_string<alda::net::port::value_type>(port_edit_.text()),
            [] { return sanguis::exception{FCPPT_TEXT("Invalid port")}; })));

    connect_text_.value(SGE_FONT_LIT("Connecting..."));

    connect_button_.text(cancel_text);
  }
  else
  {
    callbacks_.cancel_connect()();

    connect_button_.text(connect_text);

    connect_text_.value(SGE_FONT_LIT(""));
  }

  connect_running_ = !connect_running_;
}
