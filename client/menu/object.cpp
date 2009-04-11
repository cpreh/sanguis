#include "object.hpp"
#include "../log.hpp"
#include "../machine.hpp"
#include "../../resolution.hpp"
#include "../../media_path.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/make_image.hpp>
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
	sge::systems::instance &_sys,
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
		sys_.image_loader(),
		sys_.input_system(),
		sys_.font_system(),
		sge::gui::skin_ptr(
			new sge::gui::skins::standard())),

	main_menu(
		m,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point(0,0))
			.size(
				sge::structure_cast<sge::gui::dim>(resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),
	main_connect(
		main_menu,
		sys_.image_loader(),
		buttons_path,
		SGE_TEXT("connect_menu")),
	main_start(
		main_menu,
		sys_.image_loader(),
		buttons_path,
		SGE_TEXT("quickstart")),
	main_exit(
		main_menu,
		sys_.image_loader(),
		buttons_path,
		SGE_TEXT("quit")),
	
	connect_menu(
		m,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point(0,0))
			.size(
				sge::structure_cast<sge::gui::dim>(
					resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),

	connect_host(
		connect_menu,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	connect_host_label(
		connect_host,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			sys_.image_loader()->load(
				labels_path/SGE_TEXT("host.png")))),
	connect_host_edit(
		connect_host,
		sge::gui::widget::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,1)),

	connect_port(
		connect_menu,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	connect_port_label(
		connect_port,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			sys_.image_loader()->load(
				labels_path/SGE_TEXT("port.png")))),
	connect_port_edit(
		connect_port,
		sge::gui::widget::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(5,1)),

	connect_connect_wrapper(
		connect_menu,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	connect_connect(
		connect_connect_wrapper,
		sys_.image_loader(),
		buttons_path,
		SGE_TEXT("connect")),
	connect_return_wrapper(
		connect_menu,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	connect_return(
		connect_return_wrapper,
		sys_.image_loader(),
		buttons_path,
		SGE_TEXT("return")),

	mb_connect(
		m,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point(0,0))
			.size(
				sge::structure_cast<sge::gui::dim>(
					resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),

	mb_connect_label(
		mb_connect,
		sge::gui::widget::parameters(),
		SGE_TEXT("foobar")),
	
	mb_connect_buttons(
		mb_connect,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	
	mb_connect_buttons_retry(
		mb_connect_buttons,
		sge::gui::widget::parameters(),
		SGE_TEXT("Retry")),

	mb_connect_buttons_cancel(
		mb_connect_buttons,
		sge::gui::widget::parameters(),
		SGE_TEXT("Cancel")),

	mover_(
		m,
		main_menu
	),

	connections_(
		sge::assign::make_container<
			sge::signal::connection_manager::container
		>
		(
			sge::signal::shared_connection(
				main_connect.register_clicked(
					boost::bind(
						&mover::reset,
						&mover_,
						boost::ref(connect_menu))))
	//					boost::ref(mb_connect))))
		)
		(
			sge::signal::shared_connection(
				main_start.register_clicked(
					boost::bind(
						&object::start_server,
						this)))
		)
		(
			sge::signal::shared_connection(
				main_exit.register_clicked(
					_callbacks.quit_))
		)
		(
			sge::signal::shared_connection(
				connect_connect.register_clicked(
					boost::bind(
						&object::connect_from_menu,
						this)))
		)
		(
			sge::signal::shared_connection(
				connect_return.register_clicked(
					boost::bind(
						&mover::reset,
						&mover_,
						boost::ref(main_menu))))
		)
		(
			sge::signal::shared_connection(
				mb_connect_buttons_retry.register_clicked(
					boost::bind(
						&object::connect,
						this,
						boost::cref(connection_host_),
						boost::cref(connection_port_))))
		)
		(
			sge::signal::shared_connection(
				mb_connect_buttons_cancel.register_clicked(
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

	mb_connect_label.text(
		SGE_TEXT("Connection to ")+
		connection_host_+
		SGE_TEXT(" on port ")+
		connection_port_+
		SGE_TEXT(" failed: \n")+
		message);
	mover_.reset(
		mb_connect);
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
		connect_host_edit.text(),
		connect_port_edit.text());
}

void sanguis::client::menu::object::connect(
	sge::string const &host,
	sge::string const &port)
{
	connection_host_ = host;
	connection_port_ = port;

	callbacks_.connect_(
		host,
		port);
	
	mb_connect_label.text(
		SGE_TEXT("Connecting to ")+
		host+
		SGE_TEXT(" on port ")+
		port);
	
	mover_.reset(
		mb_connect);
}

void sanguis::client::menu::object::cancel_connect()
{
	mover_.reset(
		connect_menu);
	
	callbacks_.cancel_connect_();
}
