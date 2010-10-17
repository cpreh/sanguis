#include "console.hpp"
#include "../messages/serialization/convert_string_vector.hpp"
#include "../messages/console_command.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/text.hpp>
#include <boost/algorithm/string/predicate.hpp>

sanguis::client::console::console(
	sge::console::gfx &_gfx,
	sge::input::keyboard::device_ptr const _keyboard,
	sge::input::keyboard::key_code::type const _toggler,
	send_callback const &_send
)
:
	gfx_(
		_gfx
	),
	input_connection_(
		_keyboard->key_callback(
			std::tr1::bind(
				&console::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	toggler_(
		_toggler
	),
	send_(
		_send
	),
	callbacks_(),
	server_connections_()
{}

fcppt::signal::auto_connection
sanguis::client::console::register_callback(
	sge::input::keyboard::key_callback const &_c
)
{
	return 
		callbacks_.connect(
			_c
		);
}

void
sanguis::client::console::register_server_command(
	fcppt::string const &name,
	fcppt::string const &description
)
{
	server_connections_.connect(
		gfx_.object().insert(
			name,
			std::tr1::bind(
				&console::server_callback,
				this,
				std::tr1::placeholders::_1
			),
			description
		)
	);
}

sge::console::gfx &
sanguis::client::console::gfx()
{
	return
		gfx_;
}

sge::console::gfx const &
sanguis::client::console::gfx() const
{
	return
		gfx_;
}

void
sanguis::client::console::input_callback(
	sge::input::keyboard::key_event const &_k
)
{
	if (_k.key().code() == toggler_ && _k.pressed())
	{
		gfx_.active(
			!gfx_.active()
		);
		return;
	}

	if (!gfx_.active())
		callbacks_(
			_k
		);
}

void
sanguis::client::console::server_callback(
	sge::console::arg_list const &args_
)
{
	send_(
		sanguis::messages::create(
			sanguis::messages::console_command(
				sanguis::messages::serialization::convert_string_vector(
					args_
				)
			)
		)
	);
}
