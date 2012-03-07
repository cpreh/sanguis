#include <sanguis/server/console.hpp>
#include <sanguis/messages/add_console_command.hpp>
#include <sanguis/messages/console_print.hpp>
#include <sanguis/messages/create.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/font/text/string.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/homogenous_pair_impl.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sanguis::server::console::console(
	sge::charconv::system &_charconv_system,
	server::send_callback const &_send,
	server::unicast_callback const &_unicast
)
:
	object_(
		SGE_FONT_TEXT_LIT('/') // TODO: is this right?
	),
	charconv_system_(
		_charconv_system
	),
	send_(_send),
	unicast_(_unicast),
	known_commands_()
{}

sanguis::server::console::~console()
{}

fcppt::signal::auto_connection
sanguis::server::console::insert(
	fcppt::string const &_command,
	sge::console::callback::function const &_callback,
	fcppt::string const &_description
)
{
	send_(
		messages::create(
			messages::add_console_command(
				sge::charconv::fcppt_string_to_utf8(
					charconv_system_,
					_command
				),
				sge::charconv::fcppt_string_to_utf8(
					charconv_system_,
					_description
				)
			)
		)
	);

	// TODO: we have to know when a command doesn't exist anymore!
	known_commands_.push_back(
		server::console_command_pair(
			_command,
			_description
		)
	);

	return
		object_.insert(
			sge::console::callback::parameters(
				_callback,
				sge::console::callback::name(
					sge::font::text::from_fcppt_string(
						_command
					)
				)
			)
			.short_description(
				sge::font::text::from_fcppt_string(
					_description
				)
			)
		);
}

void
sanguis::server::console::eval(
	server::player_id const _id,
	sge::console::arg_list _args
)
{
	_args.push_back(
		fcppt::insert_to_string<
			sge::font::text::string
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
	server::player_id const _id,
	fcppt::string const &_line
)
{
	unicast_(
		_id,
		sanguis::messages::create(
			sanguis::messages::console_print(
				sge::charconv::fcppt_string_to_utf8(
					charconv_system_,
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
