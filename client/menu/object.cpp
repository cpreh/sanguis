#include "object.hpp"
#include "../log.hpp"
#include "../machine.hpp"
#include "../../resolution.hpp"
#include "../../media_path.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/default_cursor.hpp>
#include <sge/image/loader.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/systems/instance.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

namespace
{
sge::log::logger mylogger(
	sanguis::client::log(),
	SGE_TEXT("menu: object: "),
	true);
}

sanguis::client::menu::object::object(
	sge::systems::instance const &_sys,
	callbacks::object const &_callbacks)
: 
	sys_(_sys),
	menu_path(
		media_path()/SGE_TEXT("menu")),
	buttons_path(
		menu_path/SGE_TEXT("buttons")),
	labels_path(
		menu_path/SGE_TEXT("labels")),

	m(
		sys_.renderer(),
		sys_.input_system(),
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				sys_.font_system())),
		sge::gui::cursor_ptr(
			new sge::gui::default_cursor(
				_sys.image_loader(),
				_sys.renderer()))),

	main_(
		m,
		buttons_path,
		sys_),
	
	connect_(
		m,
		buttons_path,
		labels_path,
		sys_),

	connect_box_(
		m,
		sys_),

	mover_(
		m,
		main_.parent
	),

	connections_(
		sge::assign::make_container<
			sge::signal::connection_manager::container
		>
		(
			sge::signal::shared_connection(
				main_.connect.register_clicked(
					boost::bind(
						&mover::reset,
						&mover_,
						boost::ref(connect_.parent))))
		)
		(
			sge::signal::shared_connection(
				main_.start.register_clicked(
					boost::bind(
						&object::start_server,
						this)))
		)
		(
			sge::signal::shared_connection(
				main_.exit.register_clicked(
					_callbacks.quit_))
		)
		(
			sge::signal::shared_connection(
				connect_.connect_.register_clicked(
					boost::bind(
						&object::connect_from_menu,
						this)))
		)
		(
			sge::signal::shared_connection(
				connect_.return_.register_clicked(
					boost::bind(
						&mover::reset,
						&mover_,
						boost::ref(main_.parent))))
		)
		(
			sge::signal::shared_connection(
				connect_box_.buttons_retry.register_clicked(
					boost::bind(
						&object::connect,
						this,
						boost::cref(connection_host_),
						boost::cref(connection_port_))))
		)
		(
			sge::signal::shared_connection(
				connect_box_.buttons_cancel.register_clicked(
					boost::bind(
						&object::cancel_connect,
						this)))
		)
	),

	callbacks_(_callbacks)
{
}

void sanguis::client::menu::object::process(
	time_type const delta)
{
	mover_.update(
		delta);
	m.update();
	m.draw();
}

void sanguis::client::menu::object::connection_error(
	sge::string const &message)
{
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("got conection error: (")
		             << message 
								 << SGE_TEXT(")"));

	connect_box_.label_.text(
		SGE_TEXT("Connection to \"")+
		connection_host_+
		SGE_TEXT("\" on port \"")+
		connection_port_+
		SGE_TEXT("\" failed: \n")+
		message);
	mover_.reset(
		connect_box_.parent);
}

void sanguis::client::menu::object::start_server()
{
	callbacks_.start_server_();
	connect(
		SGE_TEXT("localhost"),
		SGE_TEXT("1337"));
}

void sanguis::client::menu::object::connect_from_menu()
{
	connect(
		connect_.host_edit.text(),
		connect_.port_edit.text());
}

void sanguis::client::menu::object::connect(
	sge::string const &host,
	sge::string const &port)
{
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("connecting to ")
		             << host 
								 << SGE_TEXT(" on port ")
								 << port);

	connection_host_ = host;
	connection_port_ = port;

	connect_box_.label_.text(
		SGE_TEXT("Connecting to \"")+
		host+
		SGE_TEXT("\" on port \"")+
		port+
		SGE_TEXT("\""));

	callbacks_.connect_(
		host,
		port);
	
	mover_.reset(
		connect_box_.parent);
}

void sanguis::client::menu::object::cancel_connect()
{
	mover_.reset(
		connect_.parent);
	
	callbacks_.cancel_connect_();
}
