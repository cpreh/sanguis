#ifndef SANGUIS_CLIENT_CONSOLE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_HPP_INCLUDED

#include "send_callback.hpp"
#include <sge/console/gfx_fwd.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/callback.hpp>
#include <sge/input/key_pair_function.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
class console
{
	FCPPT_NONCOPYABLE(console)
public:
	explicit
	console(
		sge::console::gfx &,
		sge::input::system_ptr,
		sge::input::key_code,
		send_callback const &
	);

	fcppt::signal::auto_connection 
	register_callback(
		sge::input::callback const &
	);
	
	sge::console::gfx &
	object();
	
	sge::console::gfx const &
	object() const;
private:
	void 
	input_callback(
		sge::input::key_pair const &
	);

	void
	fallback(
		fcppt::string const &
	);

	sge::console::gfx &object_;

	fcppt::signal::scoped_connection const
		input_connection_,
		fallback_connection_;

	sge::input::key_code const toggler_;

	send_callback const send_;

	fcppt::signal::object<
		sge::input::key_pair_function
	> callbacks_;

};
}
}

#endif