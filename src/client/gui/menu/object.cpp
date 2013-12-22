#include <sanguis/duration.hpp>
#include <sanguis/client/config/settings/object.hpp>
//#include <sanguis/client/gui/menu/connection_box.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/get_or_create.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/set_or_create.hpp>
#include <sge/parse/ini/string.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_fwd.hpp>
//#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::parse::ini::section_name const
config_section(
	FCPPT_TEXT("gui_menu")
);

sge::parse::ini::entry_name const
	config_hostname_key(
		FCPPT_TEXT("hostname")
	),
	config_port_key(
		FCPPT_TEXT("port")
	),
	config_quickstart_port_key(
		FCPPT_TEXT("quickstartport")
	);
}

sanguis::client::gui::menu::object::object(
	sge::renderer::device::ffp &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::font::object &_font,
	sge::input::cursor::object &_cursor,
	sge::input::keyboard::device &_keyboard,
	sanguis::client::config::settings::object &_settings,
	sanguis::client::gui::menu::callbacks::object const &_callbacks
)
:
	settings_(
		_settings
	),
	gui_context_(),
	callbacks_(
		_callbacks
	),
	quickstart_button_(
		_renderer,
		_font,
		SGE_FONT_LIT("Quickstart")
	),
	quit_button_(
		_renderer,
		_font,
		SGE_FONT_LIT("Quit")
	),
	main_container_(
		gui_context_,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					quickstart_button_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					quit_button_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	gui_master_(
		_renderer,
		_viewport_manager,
		_keyboard,
		_cursor,
		gui_context_,
		main_container_
	),
	quickstart_connection_(
		quickstart_button_.click(
			std::bind(
				&sanguis::client::gui::menu::object::handle_quickstart,
				this
			)
		)
	),
	quit_connection_(
		quit_button_.click(
			callbacks_.quit()
		)
	)
	/*,
	hostname_change_connection_(
		hostname_edit_.subscribeEvent(
			CEGUI::Window::EventTextChanged,
			CEGUI::Event::Subscriber(
				std::bind(
					&sanguis::client::gui::menu::object::handle_text_changed,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	port_change_connection_(
		port_edit_.subscribeEvent(
			CEGUI::Window::EventTextChanged,
			CEGUI::Event::Subscriber(
				std::bind(
					&sanguis::client::gui::menu::object::handle_text_changed,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	connection_box_(
		fcppt::make_unique_ptr<
			sanguis::client::gui::menu::connection_box
		>(
			gui_,
			scoped_layout_.window(),
			std::bind(
				&sanguis::client::gui::menu::object::handle_cancel_connect,
				this
			),
			std::bind(
				&sanguis::client::gui::menu::object::handle_retry_connect,
				this
			)
		)
	)*/
{
/*
	connect_button_.setEnabled(
		false
	);

	hostname_edit_.setText(
		sge::cegui::to_cegui_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_hostname_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	);

	port_edit_.setText(
		sge::cegui::to_cegui_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_port_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	);*/
}

sanguis::client::gui::menu::object::~object()
{
/*
	sge::parse::ini::set_or_create(
		settings_.sections(),
		config_section,
		config_port_key,
		sge::parse::ini::value(
			sge::cegui::from_cegui_string(
				port_edit_.getText()
			)
		)
	);

	sge::parse::ini::set_or_create(
		settings_.sections(),
		config_section,
		config_hostname_key,
		sge::parse::ini::value(
			sge::cegui::from_cegui_string(
				hostname_edit_.getText()
			)
		)
	);*/
}

void
sanguis::client::gui::menu::object::process(
	sanguis::duration const &_delta
)
{
	gui_master_.update(
		std::chrono::duration_cast<
			sanguis::gui::duration
		>(
			_delta
		)
	);
}

void
sanguis::client::gui::menu::object::draw(
	sge::renderer::context::ffp &_render_context
)
{
	_render_context.clear(
		sge::renderer::clear::parameters()
		.back_buffer(
			sge::image::color::predef::black()
		)
	);

	gui_master_.draw(
		_render_context
	);
}

/*
void
sanguis::client::gui::menu::object::connection_error(
	fcppt::string const &_message
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("got conection error: (")
			<< _message
			<< FCPPT_TEXT(')')
	);

	connection_box_->show_error(
		_message
	);
}*/

void
sanguis::client::gui::menu::object::handle_quickstart()
{
	callbacks_.quickstart()(
		alda::net::port(
			fcppt::extract_from_string_exn<
				alda::net::port::value_type
			>(
				sge::parse::ini::get_or_create(
					settings_.sections(),
					config_section,
					config_quickstart_port_key,
					sge::parse::ini::value(
						FCPPT_TEXT("31337")
					)
				).get()
			)
		)
	);
}

/*
bool
sanguis::client::gui::menu::object::handle_connect(
	CEGUI::EventArgs const &
)
{
	connection_box_->activate();

	this->do_connect();

	return true;
}

bool
sanguis::client::gui::menu::object::handle_text_changed(
	CEGUI::EventArgs const &
)
{
	typedef unsigned long port_type;

	typedef fcppt::optional<
		port_type
	> optional_port;

	optional_port const opt_port(
		fcppt::extract_from_string<
			port_type
		>(
			sge::cegui::from_cegui_string(
				port_edit_.getText()
			)
		)
	);

	connect_button_.setEnabled(
		opt_port
		&&
		!hostname_edit_.getText().empty()
		&&
		(*opt_port > 0)
		&& (*opt_port < 65535)
	);

	return true;
}

void
sanguis::client::gui::menu::object::handle_cancel_connect()
{
	connection_box_->deactivate();

	callbacks_.cancel_connect()();
}

void
sanguis::client::gui::menu::object::handle_retry_connect()
{
	this->do_connect();
}

void
sanguis::client::gui::menu::object::do_connect()
{
	callbacks_.connect()(
		alda::net::host(
			fcppt::to_std_string(
				sge::cegui::from_cegui_string(
					hostname_edit_.getText()
				)
			)
		),
		alda::net::port(
			fcppt::extract_from_string_exn<
				alda::net::port::value_type
			>(
				sge::cegui::from_cegui_string(
					port_edit_.getText()
				)
			)
		)
	);
}
*/
