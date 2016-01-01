#include <sanguis/duration.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/needed_width_from_strings.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/text_callback.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/get_or_create.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/set_or_create.hpp>
#include <sge/parse/ini/string.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/const.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
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
	),
	config_player_name_key(
		FCPPT_TEXT("playername")
	);

sge::font::string const
connect_text(
	SGE_FONT_LIT("Connect")
);

sge::font::string const
cancel_text(
	SGE_FONT_LIT("Cancel")
);

}

sanguis::client::gui::menu::object::object(
	sge::renderer::system const &_renderer_system,
	sge::renderer::device::ffp &_renderer,
	sge::renderer::device::index const _renderer_index,
	sge::viewport::manager &_viewport_manager,
	sge::font::object &_font,
	sge::input::cursor::object &_cursor,
	sge::input::focus::object &_focus,
	sanguis::client::config::settings::object &_settings,
	sanguis::client::gui::menu::callbacks::object const &_callbacks,
	sge::gui::style::base const &_gui_style
)
:
	settings_(
		_settings
	),
	renderer_(
		_renderer
	),
	gui_context_(),
	callbacks_(
		_callbacks
	),
	quickstart_button_(
		_gui_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Quickstart"),
		sge::gui::optional_needed_width()
	),
	resolution_chooser_(
		gui_context_,
		_gui_style,
		_font,
		_renderer_system,
		_renderer,
		_renderer_index
	),
	player_name_label_(
		_gui_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Name: "),
		sanguis::client::gui::default_text_color()
	),
	player_name_edit_(
		_gui_style,
		_renderer,
		_font,
		sge::font::from_fcppt_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_player_name_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	),
	player_name_line_(
		gui_context_,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					player_name_label_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					player_name_edit_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x
	),
	hostname_label_(
		_gui_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Hostname: "),
		sanguis::client::gui::default_text_color()
	),
	hostname_edit_(
		_gui_style,
		_renderer,
		_font,
		sge::font::from_fcppt_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_hostname_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	),
	hostname_line_(
		gui_context_,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					hostname_label_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					hostname_edit_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x
	),
	port_label_(
		_gui_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Port: "),
		sanguis::client::gui::default_text_color()
	),
	port_edit_(
		_gui_style,
		_renderer,
		_font,
		sge::font::from_fcppt_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_port_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	),
	port_line_(
		gui_context_,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					port_label_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					port_edit_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x
	),
	connect_text_(
		_gui_style,
		_renderer,
		_font,
		SGE_FONT_LIT(""),
		sanguis::client::gui::default_text_color(),
		sge::gui::optional_needed_width()
	),
	connect_button_(
		_gui_style,
		_renderer,
		_font,
		connect_text,
		sge::gui::optional_needed_width(
			sge::gui::needed_width_from_strings(
				_font,
				sge::gui::string_container{
					connect_text,
					cancel_text
				}
			)
		)
	),
	connect_box_(
		gui_context_,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					hostname_line_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					port_line_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					connect_text_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					connect_button_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::y
	),
	connect_frame_(
		_gui_style,
		connect_box_
	),
	quit_button_(
		_gui_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Quit"),
		sge::gui::optional_needed_width()
	),
	main_container_(
		gui_context_,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					quickstart_button_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					resolution_chooser_.widget()
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					player_name_line_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					connect_frame_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					quit_button_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::y
	),
	gui_area_(
		_renderer,
		_viewport_manager,
		main_container_
	),
	gui_master_(
		_focus,
		_cursor,
		gui_context_,
		gui_area_
	),
	gui_background_(
		gui_area_
	),
	connect_running_{
		false
	},
	quickstart_connection_(
		quickstart_button_.click(
			sge::gui::click_callback{
				std::bind(
					&sanguis::client::gui::menu::object::handle_quickstart,
					this
				)
			}
		)
	),
	connect_connection_(
		connect_button_.click(
			sge::gui::click_callback{
				std::bind(
					&sanguis::client::gui::menu::object::handle_connect,
					this
				)
			}
		)
	),
	quit_connection_(
		quit_button_.click(
			sge::gui::click_callback{
				callbacks_.quit()
			}
		)
	),
	hostname_change_connection_(
		hostname_edit_.text_change(
			sge::gui::text_callback{
				std::bind(
					&sanguis::client::gui::menu::object::handle_text_changed,
					this
				)
			}
		)
	),
	port_change_connection_(
		port_edit_.text_change(
			sge::gui::text_callback{
				std::bind(
					&sanguis::client::gui::menu::object::handle_text_changed,
					this
				)
			}
		)
	)
{
	this->handle_text_changed();
}

sanguis::client::gui::menu::object::~object()
{
	auto const save_setting(
		[
			this
		](
			sge::parse::ini::entry_name const &_entry,
			sge::font::string const &_value
		)
		{
			sge::parse::ini::set_or_create(
				settings_.sections(),
				config_section,
				_entry,
				sge::parse::ini::value(
					sge::font::to_fcppt_string(
						_value
					)
				)
			);
		}
	);

	save_setting(
		config_port_key,
		port_edit_.text()
	);

	save_setting(
		config_hostname_key,
		hostname_edit_.text()
	);

	save_setting(
		config_player_name_key,
		player_name_edit_.text()
	);
}

void
sanguis::client::gui::menu::object::process(
	sanguis::duration const &_delta
)
{
	gui_master_.update(
		sanguis::client::gui::to_duration(
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

	gui_master_.draw_with_states(
		renderer_,
		_render_context,
		gui_background_
	);
}

void
sanguis::client::gui::menu::object::connection_error(
	fcppt::string const &_message
)
{
	connect_text_.value(
		sge::font::from_fcppt_string(
			_message
		)
	);

	connect_button_.text(
		connect_text
	);

	connect_running_ =
		false;
}

fcppt::string
sanguis::client::gui::menu::object::player_name() const
{
	return
		sge::font::to_fcppt_string(
			player_name_edit_.text()
		);
}

void
sanguis::client::gui::menu::object::handle_quickstart()
{
	if(
		connect_running_
	)
		return;

	connect_running_ =
		true;

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

void
sanguis::client::gui::menu::object::handle_text_changed()
{
	typedef
	unsigned long
	port_type;

	connect_button_.enable(
		fcppt::optional::maybe(
			fcppt::extract_from_string<
				port_type
			>(
				port_edit_.text()
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				port_type const _port
			)
			{
				return
					!hostname_edit_.text().empty()
					&&
					_port > 0
					&&
					_port < 65535;
			}
		)
	);
}

void
sanguis::client::gui::menu::object::handle_connect()
{
	if(
		!connect_running_
	)
	{
		callbacks_.connect()(
			alda::net::host(
				fcppt::to_std_string(
					sge::font::to_fcppt_string(
						hostname_edit_.text()
					)
				)
			),
			alda::net::port(
				fcppt::extract_from_string_exn<
					alda::net::port::value_type
				>(
					port_edit_.text()
				)
			)
		);

		connect_text_.value(
			SGE_FONT_LIT("Connecting...")
		);

		connect_button_.text(
			cancel_text
		);
	}
	else
	{
		callbacks_.cancel_connect()();

		connect_button_.text(
			connect_text
		);

		connect_text_.value(
			SGE_FONT_LIT("")
		);
	}

	connect_running_ =
		!connect_running_;
}
