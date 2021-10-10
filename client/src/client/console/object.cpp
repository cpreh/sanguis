#include <sanguis/client/from_console_arg_list.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/messages/client/console_command.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/convert/to_string_vector.hpp>
#include <sanguis/messages/roles/console_command.hpp>
#include <alda/message/init_record.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/gfx/input_active.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/object_ref.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::console::object::object(
    sge::console::gfx::object_ref const _gfx, sanguis::client::send_callback &&_send)
    : gfx_(_gfx), send_(std::move(_send)), server_connections_()
{
}

sanguis::client::console::object::~object() = default;

void sanguis::client::console::object::register_server_command(
    fcppt::string const &_name, fcppt::string const &_description)
{
  server_connections_.push_back(gfx_->console_object().insert(
      sge::console::callback::parameters(
          sge::console::callback::function{
              [this](sge::console::arg_list const &_args, sge::console::object_ref)
              { this->server_callback(_args); }},
          sge::console::callback::name(sge::font::from_fcppt_string(_name)))
          .short_description(sge::font::from_fcppt_string(_description))));
}

void sanguis::client::console::object::draw(sge::renderer::context::ffp &_context)
{
  gfx_->render(_context, sge::console::gfx::input_active{true});
}

void sanguis::client::console::object::input_event(sge::input::event_base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic<sge::input::focus::event::base const>(_event),
      [this](fcppt::reference<sge::input::focus::event::base const> const _focus_event)
      { gfx_->focus_event(_focus_event.get()); });
}

sge::console::object &sanguis::client::console::object::sge_console()
{
  return gfx_->console_object();
}

void sanguis::client::console::object::server_callback(sge::console::arg_list const &_args)
{
  send_(sanguis::messages::client::create(
      alda::message::init_record<sanguis::messages::client::console_command>(
          sanguis::messages::roles::console_command{} =
              sanguis::messages::convert::to_string_vector(
                  sanguis::client::from_console_arg_list(_args)))));
}
