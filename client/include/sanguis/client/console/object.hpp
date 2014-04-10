#ifndef SANGUIS_CLIENT_CONSOLE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_OBJECT_HPP_INCLUDED

#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/console/object_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/connection_manager.hpp>


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
	active(
		bool
	);

	bool
	active() const;

	void
	draw(
		sge::renderer::context::ffp &
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

	fcppt::signal::connection_manager server_connections_;
};

}
}
}

#endif
