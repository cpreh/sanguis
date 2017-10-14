#ifndef SANGUIS_CLIENT_CONSOLE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_OBJECT_HPP_INCLUDED

#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/console/object_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/object_fwd.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/auto_connection_container.hpp>


namespace sanguis
{
namespace client
{
namespace console
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::console::gfx::object &,
		sanguis::client::send_callback const &
	);

	~object();

	void
	register_server_command(
		fcppt::string const &name,
		fcppt::string const &description
	);

	void
	draw(
		sge::renderer::context::ffp &
	);

	void
	input_event(
		sge::input::event_base const &
	);

	sge::console::object &
	sge_console();
private:
	void
	server_callback(
		sge::console::arg_list const &
	);

	sge::console::gfx::object &gfx_;

	sanguis::client::send_callback const send_;

	fcppt::signal::auto_connection_container server_connections_;
};

}
}
}

#endif
