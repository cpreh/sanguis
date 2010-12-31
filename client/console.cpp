#include "console.hpp"
#include "../messages/console_command.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include "../messages/serialization/convert_string_vector.hpp"
#include "../from_console_arg_list.hpp"
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
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
	sge::input::keyboard::key_callback const &_ccallback
)
{
	return 
		callbacks_.connect(
			_ccallback
		);
}

void
sanguis::client::console::register_server_command(
	fcppt::string const &_name,
	fcppt::string const &_description
)
{
	server_connections_.add(
		gfx_.object().insert(
			sge::font::text::from_fcppt_string(
				_name
			),
			std::tr1::bind(
				&console::server_callback,
				this,
				std::tr1::placeholders::_1
			),
			sge::font::text::from_fcppt_string(
				_description
			)
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
	sge::input::keyboard::key_event const &_event
)
{
	if(
		_event.key().code() == toggler_
		&& _event.pressed()
	)
	{
		gfx_.active(
			!gfx_.active()
		);

		return;
	}

	if(
		!gfx_.active()
	)
		callbacks_(
			_event
		);
}

void
sanguis::client::console::server_callback(
	sge::console::arg_list const &_args
)
{
	send_(
		sanguis::messages::create(
			sanguis::messages::console_command(
				sanguis::messages::serialization::convert_string_vector(		
					sanguis::from_console_arg_list(
						_args
					)
				)
			)
		)
	);
}
