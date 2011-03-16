#ifndef SANGUIS_SERVER_CONSOLE_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_HPP_INCLUDED

#include "console_fwd.hpp"
#include "send_callback.hpp"
#include "unicast_callback.hpp"
#include "console_command_vector.hpp"
#include "../net/id.hpp"
#include <sge/console/object.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/callback.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/homogenous_pair_decl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace server
{

class console
{
	FCPPT_NONCOPYABLE(
		console
	);
public:
	explicit console(
		server::send_callback const &,
		server::unicast_callback const &
	);

	~console();

	fcppt::signal::auto_connection
	insert(
		fcppt::string const &command,
		sge::console::callback const &,
		fcppt::string const &description
	);

	void
	eval(
		net::id,
		sge::console::arg_list
	);

	void
	print_line(
		net::id,
		fcppt::string const &
	);

	console_command_vector const &
	known_commands() const;
private:
	sge::console::object object_;

	server::send_callback const send_;

	server::unicast_callback const unicast_;

	console_command_vector known_commands_;
};

}
}

#endif
