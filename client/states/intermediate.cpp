#include "intermediate.hpp"
#include "connecting.hpp"
#include "../machine.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size_t.hpp>
#include <sge/renderer/device.hpp>
#include <sge/gui/skins/standard.hpp>
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
#include <ostream>

sanguis::client::states::intermediate::intermediate(
	my_context ctx) 
:
	my_base(ctx),
	m(
		context<machine>().sys().renderer(),
		context<machine>().sys().image_loader(),
		context<machine>().sys().input_system(),
		context<machine>().sys().font_system(),
		sge::gui::skin_ptr(new sge::gui::skins::standard())),
	top(
		m,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point(100,100))
			.size(
				sge::gui::dim(500,300))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>(
					boost::ref(top)))),

	host(
		top,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>(
					boost::ref(host)))),
	host_label(
		host,
		sge::gui::widget::parameters(),
		SGE_TEXT("Hostname:")),
	host_edit(
		host,
		sge::gui::widget::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,1)),

	port(
		top,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>(
					boost::ref(port)))),
	port_label(
		port,
		sge::gui::widget::parameters(),
		SGE_TEXT("Port:")),
	port_edit(
		port,
		sge::gui::widget::parameters(),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(5,1)),

	connect_(
		top,
		sge::gui::widget::parameters(),
		SGE_TEXT("Connect")),
	return_menu(
		top,
		sge::gui::widget::parameters(),
		SGE_TEXT("Return")),

	main_menu(
		m,
		sge::gui::widget::parameters()
			.pos(sge::gui::point(100,100))
			.size(sge::gui::dim(300,400))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>(
					boost::ref(main_menu)))),
	menu_connect(
		main_menu,
		sge::gui::widget::parameters(),
		SGE_TEXT("Connect to server")),
	menu_start(
		main_menu,
		sge::gui::widget::parameters(),
		SGE_TEXT("Start server")),
	menu_exit(
		main_menu,
		sge::gui::widget::parameters(),
		SGE_TEXT("Exit")),

	mover_(
		top,
		main_menu),
	connect_to_server_menu(
		menu_connect.clicked.connect(
			boost::bind(&menu_mover::connect_to_server,&mover_))),
	return_to_main_menu(
		return_menu.clicked.connect(
			boost::bind(&menu_mover::return_to_menu,&mover_))),
	connect_clicked(
		connect_.clicked.connect(
			boost::bind(&intermediate::connect,this))),
	start_server_clicked(
		menu_start.clicked.connect(
			boost::bind(&intermediate::start_server,this))),
	menu_exit_clicked(
		menu_exit.clicked.connect(
			boost::bind(&machine::quit,&(context<machine>())))),

	connect_now(false)
{}

boost::statechart::result
sanguis::client::states::intermediate::react(
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
sanguis::client::states::intermediate::react(
	tick_event const &t)
{
	if (connect_now)
	{
		context<machine>().connect();
		return transit<connecting>();
	}

	context<machine>().dispatch();
	mover_.update(t.delta());
	m.draw();

	return discard_event();
}

sge::log::logger &
sanguis::client::states::intermediate::log()
{
	static sge::log::logger log_(
		client::log(),
		SGE_TEXT("states::intermediate: "));
	return log_;
}

void sanguis::client::states::intermediate::connect()
{
	connect_now = true;
}

void sanguis::client::states::intermediate::start_server()
{
	connect_now = true;
}
