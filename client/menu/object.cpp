#include "object.hpp"
#include "../log.hpp"
#include "../machine.hpp"
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
#include <sge/image/file.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/device.hpp>
#include <sge/systems/instance.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/font/text/to_fcppt_string.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("menu: object")
	)
);

}

sanguis::client::menu::object::object(
	config::settings::object &_settings,
	sge::renderer::device_ptr const _renderer,
	sge::image::multi_loader &_image_loader,
	sge::font::metrics_ptr const _font_metrics,
	sge::input::keyboard::device_ptr const _keyboard,
	sge::input::mouse::device_ptr const _mouse,
	cursor::object_ptr const _cursor,
	callbacks::object const &_callbacks
)
: 
	menu_path_(
		sanguis::media_path() / FCPPT_TEXT("menu")
	),
	buttons_path_(
		menu_path_ / FCPPT_TEXT("buttons")
	),
	labels_path_(
		menu_path_ / FCPPT_TEXT("labels")
	),
	manager_(
		_renderer,
		_keyboard,
		_mouse,
		sge::gui::skins::ptr(
			fcppt::make_unique_ptr<
				sge::gui::skins::standard
			>(
				_font_metrics
			)
		),
		_cursor
	),
	main_(
		manager_,
		fcppt::math::dim::structure_cast<
			sge::gui::dim
		>(
			_renderer->screen_size()
		),
		buttons_path_,
		_image_loader
	),
	connect_(
		_settings,
		manager_,
		buttons_path_,
		labels_path_,
		_image_loader
	),
	connect_box_(
		manager_
	),
	highscore_(
		manager_,
		buttons_path_
	),
	mover_(
		manager_,
		fcppt::math::dim::structure_cast<
			sge::gui::dim
		>(
			_renderer->screen_size()
		),
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
	sprite_system_(
		_renderer
	),
	background_(
		sprite_parameters()
			.pos(
				sprite_object::point::null()
			)
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw
				>(
					_renderer->create_texture(
						_image_loader.load(
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
	time_type const _delta
)
{
	mover_.update(
		_delta
	);

	manager_.update();

	sge::sprite::render_one(
		sprite_system_,
		background_
	);

	manager_.draw();
}

void
sanguis::client::menu::object::connection_error(
	fcppt::string const &_message
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("got conection error: (")
			<< _message 
			<< FCPPT_TEXT(")")
	);

	connect_box_.label_.text(
		sge::font::text::from_fcppt_string(
			FCPPT_TEXT("Connection to \"")+
			connection_host_+
			FCPPT_TEXT("\" on port \"")+
			connection_port_+
			FCPPT_TEXT("\" failed: \n")+
			_message
		)
	);

	mover_.reset(
		connect_box_.parent
	);
}

void
sanguis::client::menu::object::start_server()
{
	callbacks_.start_server_();

	connect(
		FCPPT_TEXT("localhost"),
		FCPPT_TEXT("1337")
	);
}

void
sanguis::client::menu::object::connect_from_menu()
{
	connect(
		sge::font::text::to_fcppt_string(
			connect_.host_edit.text()
		),
		sge::font::text::to_fcppt_string(
			connect_.port_edit.text()
		)
	);
}

void
sanguis::client::menu::object::connect(
	fcppt::string const &_host,
	fcppt::string const &_port
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("connecting to ")
			<< _host 
			<< FCPPT_TEXT(" on port ")
			<< _port
	);

	connection_host_ = _host;
	connection_port_ = _port;

	connect_box_.label_.text(
		sge::font::text::from_fcppt_string(
			FCPPT_TEXT("Connecting to \"")+
			_host+
			FCPPT_TEXT("\" on port \"")+
			_port+
			FCPPT_TEXT("\"")
		)
	);

	callbacks_.connect_(
		_host,
		_port
	);
	
	mover_.reset(
		connect_box_.parent
	);
}

void
sanguis::client::menu::object::cancel_connect()
{
	mover_.reset(
		connect_.parent
	);
	
	callbacks_.cancel_connect_();
}
