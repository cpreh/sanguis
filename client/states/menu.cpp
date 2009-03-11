#include "menu.hpp"
#include "connecting.hpp"
#include "../../media_path.hpp"
#include "../machine.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/systems/instance.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <sge/iconv.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/structure_cast.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <ostream>

sanguis::client::states::menu::menu(
	my_context ctx) 
:
	my_base(ctx),
	menu_path(media_path()/SGE_TEXT("menu")),
	buttons_path(menu_path/SGE_TEXT("buttons")),
	labels_path(menu_path/SGE_TEXT("labels")),
	m(
		context<machine>().sys().renderer(),
		context<machine>().sys().image_loader(),
		context<machine>().sys().input_system(),
		context<machine>().sys().font_system(),
		sge::gui::skin_ptr(new sge::gui::skins::standard())),

	main_menu(
		m,
		sge::gui::widget::parameters()
			.pos(sge::gui::point(0,0))
			.size(sge::gui::dim(1024,768))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>(
					boost::ref(main_menu)))),
	main_connect(
		main_menu,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect_menu")/SGE_TEXT("normal.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect_menu")/SGE_TEXT("hover.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect_menu")/SGE_TEXT("keyboard.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect_menu")/SGE_TEXT("hover_keyboard.png")))),
	main_start(
		main_menu,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quickstart")/SGE_TEXT("normal.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quickstart")/SGE_TEXT("hover.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quickstart")/SGE_TEXT("keyboard.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quickstart")/SGE_TEXT("hover_keyboard.png")))),
	main_exit(
		main_menu,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quit")/SGE_TEXT("normal.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quit")/SGE_TEXT("hover.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quit")/SGE_TEXT("keyboard.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("quit")/SGE_TEXT("hover_keyboard.png")))),

#ifndef SANGUIS_STATES_MENU_DEBUG
	connect_menu(
		m,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point(0,0))
			.size(
				sge::gui::dim(1024,768))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>(
					boost::ref(connect_menu)))),

	connect_host(
		connect_menu,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>(
					boost::ref(connect_host)))),
	connect_host_label(
		connect_host,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
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
				sge::make_shared_ptr<sge::gui::layouts::horizontal>(
					boost::ref(connect_port)))),
	connect_port_label(
		connect_port,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
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
				sge::make_shared_ptr<sge::gui::layouts::horizontal>(
					boost::ref(connect_connect_wrapper)))),
	connect_connect(
		connect_connect_wrapper,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect")/SGE_TEXT("normal.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect")/SGE_TEXT("hover.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect")/SGE_TEXT("keyboard.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("connect")/SGE_TEXT("hover_keyboard.png")))),
	connect_return_wrapper(
		connect_menu,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>(
					boost::ref(connect_return_wrapper)))),
	connect_return(
		connect_return_wrapper,
		sge::gui::widget::parameters(),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("return")/SGE_TEXT("normal.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("return")/SGE_TEXT("hover.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("return")/SGE_TEXT("keyboard.png"))),
		sge::gui::make_image(
			context<machine>().sys().image_loader()->load(
				buttons_path/SGE_TEXT("return")/SGE_TEXT("hover_keyboard.png")))),

	mover_(
		connect_menu,
		main_menu),

	main_connect_conn(
		main_connect.register_clicked(
			boost::bind(&menu_mover::connect_to_server,&mover_))),

	main_start_conn(
		main_start.register_clicked(
			boost::bind(&menu::start_server,this))),

	main_exit_conn(
		main_exit.register_clicked(
			boost::bind(&machine::quit,&(context<machine>())))),

	connect_connect_conn(
		connect_connect.register_clicked(
			boost::bind(&menu::connect,this))),

	connect_return_conn(
		connect_return.register_clicked(
			boost::bind(&menu_mover::return_to_menu,&mover_))),
#endif

	connect_now(false)
{}

boost::statechart::result
sanguis::client::states::menu::react(
	message_event const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("got unexpected event ")
			<< sge::iconv(typeid(*m.message).name()));
	return defer_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	tick_event const &t)
{
	if (connect_now)
	{
		context<machine>().connect();
		return transit<connecting>();
	}

	context<machine>().dispatch();
#ifndef SANGUIS_STATES_MENU_DEBUG
	mover_.update(t.delta());
#endif
	m.draw();

	return discard_event();
}

sge::log::logger &
sanguis::client::states::menu::log()
{
	static sge::log::logger log_(
		client::log(),
		SGE_TEXT("states::menu: "),
		true
	);
	return log_;
}

void sanguis::client::states::menu::connect()
{
#ifndef SANGUIS_STATES_MENU_DEBUG
	context<machine>().address(
		sge::iconv(
			connect_host_edit.text()
		)
	);
	context<machine>().port(
		boost::lexical_cast<net::port_type>(
			connect_port_edit.text()));
#endif
	connect_now = true;
}

void sanguis::client::states::menu::start_server()
{
	connect_now = true;
}
