#include <sanguis/client/from_console_arg_list.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/messages/client/console_command.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/convert/to_string_vector.hpp>
#include <sanguis/messages/roles/console_command.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::console::object::object(
	sge::console::gfx::object &_gfx,
	sanguis::client::send_callback const &_send
)
:
	gfx_(
		_gfx
	),
	send_(
		_send
	),
	server_connections_()
{
}

sanguis::client::console::object::~object()
{
}

void
sanguis::client::console::object::register_server_command(
	fcppt::string const &_name,
	fcppt::string const &_description
)
{
	server_connections_.push_back(
		gfx_.console_object().insert(
			sge::console::callback::parameters(
				std::bind(
					&sanguis::client::console::object::server_callback,
					this,
					std::placeholders::_1
				),
				sge::console::callback::name(
					sge::font::from_fcppt_string(
						_name
					)
				)
			)
			.short_description(
				sge::font::from_fcppt_string(
					_description
				)
			)
		)
	);
}

void
sanguis::client::console::object::active(
	bool const _active
)
{
	gfx_.active(
		_active
	);
}

bool
sanguis::client::console::object::active() const
{
	return
		gfx_.active();
}

void
sanguis::client::console::object::draw(
	sge::renderer::context::ffp &_context
)
{
	if(
		this->active()
	)
		gfx_.render(
			_context
		);
}

sge::console::object &
sanguis::client::console::object::sge_console()
{
	return
		gfx_.console_object();
}

void
sanguis::client::console::object::server_callback(
	sge::console::arg_list const &_args
)
{
	send_(
		sanguis::messages::client::create(
			sanguis::messages::client::console_command(
				sanguis::messages::roles::console_command{} =
					sanguis::messages::convert::to_string_vector(
						sanguis::client::from_console_arg_list(
							_args
						)
					)
			)
		)
	);
}
