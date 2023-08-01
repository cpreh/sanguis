#include <sanguis/duration.hpp>
#include <sanguis/io_service_callback.hpp>
#include <sanguis/log_level_streams.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/client/create_systems.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/client/object.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/server.hpp>
#include <sanguis/client/server_callback.hpp>
#include <sanguis/client/systems.hpp>
#include <sanguis/client/args/result.hpp>
#include <sanguis/client/args/labels/history_size.hpp>
#include <sanguis/client/config/settings/file.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/style/simple.hpp>
#include <sanguis/client/states/menu.hpp>
#include <alda/net/port.hpp>
#include <sge/audio/player.hpp>
#include <sge/config/media_path.hpp>
#include <sge/console/prefix.hpp>
#include <sge/font/added.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/timer/absolute_impl.hpp>
#include <sge/timer/difference_and_reset.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/log/level_stream.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <exception>
#include <ostream>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::object::object(
    fcppt::log::context_reference const _log_context, sanguis::client::args::result const &_args)
    : sanguis::client::object_base(),
      log_context_{_log_context},
      log_{
          _log_context,
          sanguis::client::log_location(),
          fcppt::log::parameters_no_function(fcppt::log::name{FCPPT_TEXT("object")})},
      settings_(_log_context, sanguis::client::config::settings::file()),
      saver_(fcppt::make_cref(settings_)),
      io_service_(),
      sys_(sanguis::client::create_systems(_log_context, _args)),
      renderer_(sys_->renderer_device_core()),
      added_font_(sys_->font_system().add_font(
          sanguis::media_path() / FCPPT_TEXT("font") / FCPPT_TEXT("Electrolize-Regular.ttf"))),
      font_object_(
          sys_->font_system().create_font(sge::font::parameters()
                                              .family(FCPPT_TEXT("Electrolize"))
                                              .ttf_size(fcppt::literal<sge::font::ttf_size>(20U)))),
      resources_(
          _log_context,
          fcppt::make_ref(sys_->image_system()),
          fcppt::make_ref(sys_->renderer_device_core()),
          fcppt::make_ref(sys_->audio_loader()),
          fcppt::make_ref(sys_->audio_player())),
      gui_style_(fcppt::unique_ptr_to_base<sge::gui::style::base>(
          fcppt::make_unique_ptr<sanguis::client::gui::style::simple>(
              fcppt::make_cref(resources_.resources().textures())))),
      console_(sge::console::prefix(SGE_FONT_LIT('/'))),
      console_gfx_(
          fcppt::make_ref(console_),
          fcppt::make_ref(sys_->renderer_device_ffp()),
          fcppt::make_ref(*font_object_),
          fcppt::make_ref(sys_->viewport_manager()),
          fcppt::record::get<sanguis::client::args::labels::history_size>(_args)),
      cursor_{
          fcppt::make_ref(sys_->renderer_device_ffp()),
          fcppt::make_cref(sys_->input_processor()),
          fcppt::make_cref(resources_.resources().textures())},
      machine_(
          _log_context,
          fcppt::make_ref(settings_),
          fcppt::copy(_args),
          sanguis::client::server_callback{[this](alda::net::port const _port)
                                           { this->create_server(_port); }},
          fcppt::make_cref(resources_),
          fcppt::make_cref(*gui_style_),
          fcppt::make_ref(sys_->window_system()),
          fcppt::make_ref(*font_object_),
          fcppt::make_ref(console_gfx_.get()),
          fcppt::make_ref(sys_->renderer_device_ffp()),
          fcppt::make_ref(io_service_),
          fcppt::make_ref(sys_->viewport_manager()),
          fcppt::make_ref(cursor_)),
      frame_timer_(),
      server_(),
      scoped_machine_(fcppt::make_ref(machine_))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::object::~object() = default;

awl::main::exit_code sanguis::client::object::run()
{
  this->register_handler();

  try
  {
    io_service_.run();
  }
  catch (fcppt::exception const &_exception)
  {
    FCPPT_LOG_FATAL(log_, fcppt::log::out << FCPPT_TEXT("Client error: ") << _exception.string())

    sys_->window_system().quit(awl::main::exit_failure());
  }
  catch (std::exception const &_exception)
  {
    FCPPT_LOG_FATAL(log_, fcppt::log::out << FCPPT_TEXT("Client error: ") << _exception.what())

    sys_->window_system().quit(awl::main::exit_failure());
  }

  awl::main::exit_code const server_ret(this->quit_server());

  return server_ret == awl::main::exit_failure() ? awl::main::exit_failure() :
                                                 // TODO(philipp): Return the actual error here
             awl::main::exit_success();
}

void sanguis::client::object::register_handler()
{
  io_service_.post(sanguis::io_service_callback{[this] { this->loop_handler(); }});
}

void sanguis::client::object::loop_handler()
{
  fcppt::optional::maybe_void(
      server_,
      [this](server_unique_ptr const &_server)
      {
        if (!_server->running())
        {
          sys_->window_system().quit(awl::main::exit_failure());
        }
      });

  if (!machine_.process(std::chrono::duration_cast<sanguis::duration>(
          sge::timer::difference_and_reset(frame_timer_))))
  {
    io_service_.stop();

    return;
  }

  this->register_handler();
}

void sanguis::client::object::create_server(alda::net::port const _port)
{
  if (server_.has_value())
  {
    this->quit_server();

    server_ = optional_server_unique_ptr();
  }
  else
  {
    // The server and the client both do logging and this ensures
    // that it's thread-safe
    for (fcppt::log::level_stream &element : sanguis::log_level_streams())
    {
      // NOLINTNEXTLINE(readability-static-accessed-through-instance)
      element.get().sync_with_stdio(true);
    }
  }

  server_ = optional_server_unique_ptr(
      fcppt::make_unique_ptr<sanguis::client::server>(log_context_, _port));
}

awl::main::exit_code sanguis::client::object::quit_server()
{
  fcppt::optional::maybe_void(server_, [](server_unique_ptr const &_server) { _server->quit(); });

  return fcppt::optional::maybe(
      server_,
      [] { return awl::main::exit_success(); },
      [](server_unique_ptr const &_server) { return _server->run(); });
}
