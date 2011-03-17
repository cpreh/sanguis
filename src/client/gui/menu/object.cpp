#include "object.hpp"
#include "../object.hpp"
#include "../../log.hpp"
#include "../../../media_path.hpp"
//#include <sge/font/text/from_fcppt_string.hpp>
//#include <sge/font/text/to_fcppt_string.hpp>
//#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIWindow.h>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("menu: object")
	)
);

}

sanguis::client::gui::menu::object::object(
	config::settings::object &_settings,
	client::gui::object &_gui,
	callbacks::object const &_callbacks
)
: 
	callbacks_(_callbacks),
	gui_(_gui),
	scoped_layout_(
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("main_menu.layout"),
		_gui.charconv_system()
	),
	quickstart_connection_(
		CEGUI::WindowManager::getSingleton().getWindow(
			"Root/FrameWindow/Quickstart"
		)
		->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::quickstart,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	)
#if 0
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
				connect_box_.buttons_cancel.register_clicked(
					std::tr1::bind(
						&object::cancel_connect,
						this
					)
				)
			)
		)
	),
#endif
{
}

sanguis::client::gui::menu::object::~object()
{
}

void
sanguis::client::gui::menu::object::process(
	time_type const _delta
)
{
	gui_.update(
		_delta
	);

	gui_.render();
}

void
sanguis::client::gui::menu::object::connection_error(
	fcppt::string const &_message
)
{
#if 0
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
#endif
}

bool
sanguis::client::gui::menu::object::quickstart(
	CEGUI::EventArgs const &
)
{
	callbacks_.quickstart()();

	// FIXME: Don't hardocde the port here!
	this->connect(
		FCPPT_TEXT("localhost"),
		FCPPT_TEXT("1337")
	);

	return true;
}

void
sanguis::client::gui::menu::object::connect_from_menu()
{
#if 0
	this->connect(
		sge::font::text::to_fcppt_string(
			connect_.host_edit.text()
		),
		sge::font::text::to_fcppt_string(
			connect_.port_edit.text()
		)
	);
#endif
}

void
sanguis::client::gui::menu::object::connect(
	fcppt::string const &_host,
	fcppt::string const &_port
)
{
#if 0
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
#endif
}

void
sanguis::client::gui::menu::object::cancel_connect()
{
#if 0
	mover_.reset(
		connect_.parent
	);
#endif	
	callbacks_.cancel_connect()();
}
