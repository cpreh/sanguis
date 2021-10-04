#ifndef SANGUIS_SERVER_CONSOLE_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_HPP_INCLUDED

#include <sanguis/server/console_command_vector.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/send_callback.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/function.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sanguis::server
{

class console
{
	FCPPT_NONMOVABLE(
		console
	);
public:
	console(
		sanguis::server::send_callback &&,
		sanguis::server::unicast_callback &&
	);

	~console();

	[[nodiscard]]
	fcppt::signal::auto_connection
	insert(
		fcppt::string const &command,
		sge::console::callback::function &&,
		fcppt::string const &description
	);

	void
	eval(
		server::player_id,
		sge::console::arg_list
	);

	void
	print_line(
		server::player_id,
		fcppt::string const &
	);

	[[nodiscard]]
	sanguis::server::console_command_vector const &
	known_commands() const;
private:
	sge::console::object object_;

	sanguis::server::send_callback const send_;

	sanguis::server::unicast_callback const unicast_;

	sanguis::server::console_command_vector known_commands_;
};

}

#endif
