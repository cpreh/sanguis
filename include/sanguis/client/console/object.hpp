#ifndef SANGUIS_CLIENT_CONSOLE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_OBJECT_HPP_INCLUDED

#include <sanguis/client/console/object_fwd.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/console/object_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

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
		sge::console::gfx &,
		sge::charconv::system &,
		client::send_callback const &
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
	draw();

	sge::console::object &
	sge_console();
private:
	void
	server_callback(
		sge::console::arg_list const &
	);

	sge::console::gfx &gfx_;

	sge::charconv::system &charconv_system_;

	send_callback const send_;

	fcppt::signal::connection_manager server_connections_;
};

}
}
}

#endif
