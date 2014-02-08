#include <sanguis/server/console.hpp>
#include <sanguis/server/console_command_pair.hpp>
#include <sanguis/server/console_command_vector.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/send_callback.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/messages/server/add_console_command.hpp>
#include <sanguis/messages/server/console_print.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/string.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/auto_connection.hpp>


sanguis::server::console::console(
	sanguis::server::send_callback const &_send,
	sanguis::server::unicast_callback const &_unicast
)
:
	object_(
		SGE_FONT_LIT('/')
	),
	send_(
		_send
	),
	unicast_(
		_unicast
	),
	known_commands_()
{
}

sanguis::server::console::~console()
{
}

fcppt::signal::auto_connection
sanguis::server::console::insert(
	fcppt::string const &_command,
	sge::console::callback::function const &_callback,
	fcppt::string const &_description
)
{
	send_(
		sanguis::messages::server::create(
			sanguis::messages::server::add_console_command(
				sge::charconv::fcppt_string_to_utf8(
					_command
				),
				sge::charconv::fcppt_string_to_utf8(
					_description
				)
			)
		)
	);

	// TODO: we have to know when a command doesn't exist anymore!
	known_commands_.push_back(
		sanguis::server::console_command_pair(
			_command,
			_description
		)
	);

	return
		object_.insert(
			sge::console::callback::parameters(
				_callback,
				sge::console::callback::name(
					sge::font::from_fcppt_string(
						_command
					)
				)
			)
			.short_description(
				sge::font::from_fcppt_string(
					_description
				)
			)
		);
}

void
sanguis::server::console::eval(
	sanguis::server::player_id const _id,
	sge::console::arg_list _args
)
{
	_args.push_back(
		fcppt::insert_to_string<
			sge::font::string
		>(
			_id
		)
	);

	object_.eval(
		_args
	);
}

void
sanguis::server::console::print_line(
	sanguis::server::player_id const _id,
	fcppt::string const &_line
)
{
	unicast_(
		_id,
		sanguis::messages::server::create(
			sanguis::messages::server::console_print(
				sge::charconv::fcppt_string_to_utf8(
					_line
				)
			)
		)
	);
}

sanguis::server::console_command_vector const &
sanguis::server::console::known_commands() const
{
	return known_commands_;
}
