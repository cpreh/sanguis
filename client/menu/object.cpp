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
#include <sge/systems/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("menu: object")
	)
);

}

#include <iostream>
#include <fcppt/math/dim/dim.hpp>

sanguis::client::menu::object::object(
	sge::renderer::device_ptr const renderer_,
	sge::image::loader_ptr const image_loader_,
	sge::font::system_ptr const font_system_,
	sge::input::system_ptr const input_system_,
	cursor::object_ptr const _cursor,
	callbacks::object const &_callbacks
)
: 
	menu_path(
		media_path()/FCPPT_TEXT("menu")
	),
	buttons_path(
		menu_path/FCPPT_TEXT("buttons")
	),
	labels_path(
		menu_path/FCPPT_TEXT("labels")
	),
	m(
		renderer_,
		input_system_,
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				font_system_
			)
		),
		_cursor
	),
	main_(
		m,
		buttons_path,
		image_loader_
	),
	connect_(
		m,
		buttons_path,
		labels_path,
		image_loader_
	),
	connect_box_(
		m
	),
	highscore_(
		m,
		buttons_path
	),
	mover_(
		m,
		main_.parent
	),
	connections_(
		fcppt::assign::make_container<
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
		renderer_
	),
	background(
		sprite_parameters()
			.pos(
				sprite_object::point::null()
			)
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw
				>(
					renderer_->create_texture(
						image_loader_->load(
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
	std::cerr << background.texture()->dim() << '\n';
}

sanguis::client::menu::object::~object()
{
}

void
sanguis::client::menu::object::process(
	time_type const delta
)
{
	std::cerr << "menu::object::process\n";

	mover_.update(
		delta
	);

	std::cerr << "menu::object::process after mover_\n";

	m.update();

	std::cerr << "menu::object::process after update\n";

	sge::sprite::render_one(
		ss,
		background
	);

	m.draw();
}

void
sanguis::client::menu::object::connection_error(
	fcppt::string const &message
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
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
	fcppt::string const &host,
	fcppt::string const &port)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
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
