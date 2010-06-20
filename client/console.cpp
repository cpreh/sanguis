#include "console.hpp"
#include "../messages/console_command.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/text.hpp>
#include <boost/algorithm/string/predicate.hpp>

sanguis::client::console::console(
	sge::console::gfx &_gfx,
	sge::input::system_ptr const _input_system,
	sge::input::key_code const _toggler,
	send_callback const &_send
)
:
	gfx_(
		_gfx
	),
	input_connection_(
		_input_system->register_callback(
			std::tr1::bind(
				&console::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	fallback_connection_(
		gfx_.object().register_fallback(
			std::tr1::bind(
				&console::fallback,
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
	callbacks_()
{}

fcppt::signal::auto_connection
sanguis::client::console::register_callback(
	sge::input::callback const &_c
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
	sge::input::key_pair const &_k
)
{
	if (_k.key().code() == toggler_ && _k.value() != 0)
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
sanguis::client::console::fallback(
	fcppt::string const &string_
)
{
	fcppt::string const prefix(
		FCPPT_TEXT("sv_")
	);

	if(
		boost::algorithm::starts_with(
			string_,
			prefix
		)
	)
		send_(
			messages::create(
				messages::console_command(
					fcppt::utf8::convert(
						string_.substr(
							prefix.size()
						)
					)
				)
			)
		);
}
