#include "console.hpp"
#include "../messages/add_console_command.hpp"
#include "../messages/console_print.hpp"
#include "../messages/create.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/homogenous_pair_impl.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sanguis::server::console::console(
	server::send_callback const &_send,
	server::unicast_callback const &_unicast
)
:
	object_(
		FCPPT_TEXT('/') // TODO: is this right?
	),
	send_(_send),
	unicast_(_unicast),
	known_commands_()
{}

sanguis::server::console::~console()
{}

fcppt::signal::auto_connection
sanguis::server::console::insert(
	fcppt::string const &command,
	sge::console::callback const &callback,
	fcppt::string const &description
)
{
	send_(
		messages::create(
			messages::add_console_command(
				fcppt::utf8::convert(
					command
				),
				fcppt::utf8::convert(
					description
				)
			)
		)
	);

	return
		object_.insert(
			command,
			callback,
			description
		);
}

void
sanguis::server::console::eval(
	net::id_type const id_,
	sge::console::arg_list args_
)
{
	args_.push_back(
		fcppt::lexical_cast<
			fcppt::string
		>(
			id_
		)
	);

	object_.eval(
		args_
	);
}

void
sanguis::server::console::print_line(
	net::id_type const id_,
	fcppt::string const &line_
)
{
	unicast_(
		id_,	
		sanguis::messages::create(
			sanguis::messages::console_print(
				fcppt::utf8::convert(
					line_
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
