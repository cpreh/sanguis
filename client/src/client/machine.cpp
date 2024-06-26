#include <sanguis/duration.hpp>
#include <sanguis/io_service.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/io_service_ref.hpp>
#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/cursor_ref.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/server_callback.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/client/config/settings/object_ref.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/net/deserialize.hpp>
#include <sanguis/client/net/serialize_to_circular_buffer.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/server/base.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <alda/net/host.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <sge/console/gfx/object_fwd.hpp>
#include <sge/console/gfx/object_ref.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/input/event_base.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp> // NOLINT(misc-include-cleaner)
#include <sge/systems/instance.hpp> // NOLINT(misc-include-cleaner)
#include <sge/viewport/manager_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <sge/window/system.hpp> // NOLINT(misc-include-cleaner)
#include <sge/window/system_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/const.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::machine::machine(
    fcppt::log::context_reference const _log_context,
    sanguis::client::config::settings::object_ref const _settings,
    sanguis::client::args::result &&_options,
    sanguis::client::server_callback &&_server_callback,
    sanguis::client::load::context_cref const _resources,
    sge::gui::style::const_reference const _gui_style,
    sge::window::system_ref const _window_system,
    sge::font::object_ref const _font_object,
    sge::console::gfx::object_ref const _console_gfx,
    sge::renderer::device::ffp_ref const _renderer,
    sanguis::io_service_ref const _io_service,
    sge::viewport::manager_ref const _viewport_manager,
    sanguis::client::cursor_ref const _cursor_gfx)
    : log_context_{_log_context},
      log_{
          _log_context,
          sanguis::client::log_location(),
          fcppt::log::name{FCPPT_TEXT("machine")}},
      settings_(_settings),
      options_(std::move(_options)),
      resources_(_resources),
      gui_style_(_gui_style),
      renderer_(_renderer),
      viewport_manager_(_viewport_manager),
      net_(alda::net::parameters(
          _log_context,
          _io_service->impl(),
          sanguis::net::send_buffer_size(),
          sanguis::net::receive_buffer_size())),
      s_conn_(net_.register_connect(
          alda::net::client::connect_callback{[this] { this->connect_callback(); }})),
      s_disconn_(net_.register_error(alda::net::client::error_callback{
          [this](fcppt::string const &_message, boost::system::error_code const &_error)
          { this->error_callback(_message, _error); }})),
      s_data_(net_.register_data(alda::net::client::data_callback{
          [this](alda::net::buffer::circular_receive::streambuf &_data)
          { this->data_callback(_data); }})),
      window_system_(_window_system),
      font_object_(_font_object),
      console_gfx_(_console_gfx),
      server_callback_(std::move(_server_callback)),
      cursor_gfx_(_cursor_gfx)
{
}

FCPPT_PP_POP_WARNING

sanguis::client::machine::~machine() = default;

void sanguis::client::machine::quickstart(alda::net::port const _port)
{
  FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("quickstart()"))

  try
  {
    server_callback_(_port);
  }
  catch (boost::system::system_error const &_error)
  {
    this->error_callback(fcppt::from_std_string(_error.what()), _error.code());

    return;
  }

  this->connect(alda::net::host("localhost"), _port);
}

void sanguis::client::machine::connect(alda::net::host const &_host, alda::net::port const _port)
{
  net_.connect(_host, _port);
}

void sanguis::client::machine::disconnect() { net_.disconnect(); }

void sanguis::client::machine::send(sanguis::messages::client::base const &_message)
{
  if (!sanguis::client::net::serialize_to_circular_buffer(_message, net_.send_buffer()))
  {
    FCPPT_LOG_ERROR(log_, fcppt::log::out << FCPPT_TEXT("Not enough space left in the send_buffer"))
    // FIXME: We have to wait for free space here!
    // Any client message except the very first message (which is part of the handshake)
    // can technically be lost, so leave this for now.
  }

  net_.queue_send();
}

bool sanguis::client::machine::process(sanguis::duration const &_time)
{
  this->process_event(sanguis::client::events::tick(_time));

  return fcppt::either::match(
      window_system_->poll(),
      [](
          // TODO(philipp): Return this from client::object
          awl::main::exit_code const /*_result*/
      ) { return false; },
      [this](awl::event::container const &_events)
      {
        for (awl::event::base_unique_ptr const &event : _events)
        {
          this->process_sge_event(*event);
        }

        return true;
      });
}

void sanguis::client::machine::quit()
{
  FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("Exiting the client!"))

  window_system_->quit(awl::main::exit_success());
}

sanguis::client::config::settings::object &sanguis::client::machine::settings()
{
  return settings_.get();
}

sanguis::client::args::result const &sanguis::client::machine::options() const { return options_; }

sge::gui::style::base const &sanguis::client::machine::gui_style() const
{
  return gui_style_.get();
}

sge::renderer::device::ffp &sanguis::client::machine::renderer() const { return renderer_.get(); }

sge::font::object &sanguis::client::machine::font_object() const { return font_object_.get(); }

sge::console::gfx::object &sanguis::client::machine::console_gfx() { return console_gfx_.get(); }

sanguis::client::load::context const &sanguis::client::machine::resources() const
{
  return resources_.get();
}

sge::viewport::manager &sanguis::client::machine::viewport_manager() const
{
  return viewport_manager_.get();
}

sanguis::client::cursor &sanguis::client::machine::cursor_gfx() const { return cursor_gfx_.get(); }

fcppt::log::context_reference sanguis::client::machine::log_context() const { return log_context_; }

void sanguis::client::machine::draw()
{
  sge::renderer::context::scoped_ffp const block(
      renderer_,
      fcppt::reference_to_base<sge::renderer::target::base>(
          fcppt::make_ref(renderer_->onscreen_target())));

  this->process_event(sanguis::client::events::render(fcppt::make_ref(block.get())));
}

void sanguis::client::machine::process_sge_event(awl::event::base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::variant::dynamic_cast_<
          fcppt::mpl::list::
              object<sge::renderer::event::render const, sge::input::event_base const>,
          fcppt::cast::dynamic_fun>(_event),
      [this](auto const &_variant)
      {
        fcppt::variant::match(
            _variant,
            [this](fcppt::reference<sge::renderer::event::render const>) { this->draw(); },
            [this](fcppt::reference<sge::input::event_base const> const _input_event)
            { this->process_event(sanguis::client::events::input(_input_event)); });
      });
}

void sanguis::client::machine::connect_callback()
{
  this->process_event(sanguis::client::events::connected());
}

void sanguis::client::machine::error_callback(
    fcppt::string const &_message, boost::system::error_code const &_error)
{
  this->process_event(sanguis::client::events::net_error(fcppt::copy(_message), _error));
}

void sanguis::client::machine::data_callback(alda::net::buffer::circular_receive::streambuf &_data)
{
  while (fcppt::optional::maybe(
      sanguis::client::net::deserialize(_data),
      fcppt::const_(false),
      [this](sanguis::messages::server::unique_ptr &&_message)
      {
        this->process_event(sanguis::client::events::message(std::move(_message)));

        return true;
      }))
  {
  }
}
