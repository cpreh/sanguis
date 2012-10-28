#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include <sanguis/client/machine.hpp>
#include <sanguis/client/systems_fwd.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/saver.hpp>
#include <sanguis/client/console/gfx.hpp>
#include <sanguis/client/cursor/object.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/server/object_fwd.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/main_object.hpp>
#include <sanguis/timer.hpp>
#include <sge/console/object.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

class object
:
	public sanguis::main_object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		boost::program_options::variables_map const &
	);

	~object();
private:
	awl::main::exit_code const
	run();

	void
	register_handler();

	void
	loop_handler();

	void
	create_server(
		alda::net::port
	);

	awl::main::exit_code const
	quit_server();

	// declare the config stuff first, so they are destroyed last
	sanguis::client::config::settings::object settings_;

	sanguis::client::config::settings::saver saver_;

	sanguis::io_service io_service_;

	typedef fcppt::scoped_ptr<
		sanguis::client::systems
	> systems_scoped_ptr;

	systems_scoped_ptr const sys_;

	sge::font::object_scoped_ptr const font_object_;

	sge::console::object console_;

	sanguis::client::console::gfx console_gfx_;

	sanguis::load::context resources_;

	sanguis::client::cursor::object cursor_;

	sanguis::client::gui::object gui_;

	sanguis::client::machine machine_;

	sanguis::timer frame_timer_;

	fcppt::scoped_ptr<
		sanguis::server::object
	> server_;

	typedef fcppt::scoped_state_machine<
		sanguis::client::machine
	> scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif
