#include "object.hpp"
#include "../log.hpp"
#include "../machine.hpp"
#include "../../resolution.hpp"
#include "../../media_path.hpp"
#include "../cursor/object.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/device.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/systems/instance.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/log/headers.hpp>
#include <fcppt/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <tr1/functional>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("menu: object")
	)
);

}

sanguis::client::menu::object::object(
	sge::systems::instance const &_sys,
	cursor::object_ptr const _cursor,
	callbacks::object const &_callbacks)
: 
	sys_(_sys),
	menu_path(
		media_path()/FCPPT_TEXT("menu")),
	buttons_path(
		menu_path/FCPPT_TEXT("buttons")),
	labels_path(
		menu_path/FCPPT_TEXT("labels")),

	m(
		sys_.renderer(),
		sys_.input_system(),
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				sys_.font_system()
			)
		),
		_cursor
	),
	main_(
		m,
		buttons_path,
		sys_
	),
	connect_(
		m,
		buttons_path,
		labels_path,
		sys_
	),
	connect_box_(
		m,
		sys_
	),
	highscore_(
		m,
		buttons_path,
		sys_
	),
	mover_(
		m,
		main_.parent
	),
	connections_(
		sge::assign::make_container<
			fcppt::signal::connection_manager::container
		>
		(
			fcppt::signal::shared_connection(
				main_.connect.register_clicked(
					std::tr1::bind(
						&mover::reset,
						&mover_,
						std::tr1::ref(connect_.parent)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				main_.start.register_clicked(
					std::tr1::bind(
						&object::start_server,
						this
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				main_.highscore.register_clicked(
					std::tr1::bind(
						&mover::reset,
						&mover_,
						std::tr1::ref(highscore_.parent)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				main_.exit.register_clicked(
					_callbacks.quit_
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				connect_.connect_.register_clicked(
					std::tr1::bind(
						&object::connect_from_menu,
						this
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				connect_.return_.register_clicked(
					std::tr1::bind(
						&mover::reset,
						&mover_,
						std::tr1::ref(main_.parent)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				connect_box_.buttons_retry.register_clicked(
					std::tr1::bind(
						&object::connect,
						this,
						std::tr1::ref(
							connection_host_
						),
						std::tr1::ref(
							connection_port_
						)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				highscore_.back_button.register_clicked(
					std::tr1::bind(
						&mover::reset,
						&mover_,
						std::tr1::ref(main_.parent)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				connect_box_.buttons_cancel.register_clicked(
					std::tr1::bind(
						&object::cancel_connect,
						this
					)
				)
			)
		)
	),

	callbacks_(
		_callbacks
	),
	ss(
		_sys.renderer()
	),
	background(
		sprite_parameters()
			.pos(
				sprite_object::point::null()
			)
			.texture(
				sge::make_shared_ptr<
					sge::texture::part_raw
				>(
					_sys.renderer()->create_texture(
						_sys.image_loader()->load(
							media_path() / FCPPT_TEXT("dirt_tile.png")
						)->view(),
						sge::renderer::filter::linear,
						sge::renderer::resource_flags::none
					)
				)
			)
			.texture_size()
			.elements()
	)
{
}

sanguis::client::menu::object::~object()
{
}

void
sanguis::client::menu::object::process(
	time_type const delta
)
{
	mover_.update(
		delta
	);

	m.update();

	sge::sprite::render_one(
		ss,
		background
	);

	m.draw();
}

void sanguis::client::menu::object::connection_error(
	sge::string const &message)
{
	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_
			<< FCPPT_TEXT("got conection error: (")
			<< message 
			<< FCPPT_TEXT(")"));

	connect_box_.label_.text(
		FCPPT_TEXT("Connection to \"")+
		connection_host_+
		FCPPT_TEXT("\" on port \"")+
		connection_port_+
		FCPPT_TEXT("\" failed: \n")+
		message);
	mover_.reset(
		connect_box_.parent);
}

void sanguis::client::menu::object::start_server()
{
	callbacks_.start_server_();
	connect(
		FCPPT_TEXT("localhost"),
		FCPPT_TEXT("1337"));
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
		sge::log::_
			<< FCPPT_TEXT("connecting to ")
			<< host 
			<< FCPPT_TEXT(" on port ")
			<< port);

	connection_host_ = host;
	connection_port_ = port;

	connect_box_.label_.text(
		FCPPT_TEXT("Connecting to \"")+
		host+
		FCPPT_TEXT("\" on port \"")+
		port+
		FCPPT_TEXT("\""));

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
