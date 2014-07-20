#include <sanguis/duration.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/needed_width_from_strings.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/string_container.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
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
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
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
	sge::input::keyboard::device &_keyboard,
	sanguis::client::load::resource::textures const &_textures,
	sanguis::client::config::settings::object &_settings,
	sanguis::client::gui::menu::callbacks::object const &_callbacks,
	sanguis::gui::style::base const &_style
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
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Quickstart"),
		sanguis::gui::optional_needed_width()
	),
	resolution_chooser_(
		gui_context_,
		_style,
		_font,
		_renderer_system,
		_renderer,
		_renderer_index
	),
	player_name_label_(
		_renderer,
		_font,
		SGE_FONT_LIT("Name: "),
		sanguis::gui::text_color(
			sge::image::color::predef::black()
		)
	),
	player_name_edit_(
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
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					player_name_label_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					player_name_edit_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	hostname_label_(
		_renderer,
		_font,
		SGE_FONT_LIT("Hostname: "),
		sanguis::gui::text_color(
			sge::image::color::predef::black()
		)
	),
	hostname_edit_(
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
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					hostname_label_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					hostname_edit_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	port_label_(
		_renderer,
		_font,
		SGE_FONT_LIT("Port: "),
		sanguis::gui::text_color(
			sge::image::color::predef::black()
		)
	),
	port_edit_(
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
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					port_label_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					port_edit_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	connect_text_(
		_renderer,
		_font,
		SGE_FONT_LIT(""),
		sanguis::gui::text_color(
			sge::image::color::predef::black()
		),
		sanguis::gui::optional_needed_width()
	),
	connect_button_(
		_style,
		_renderer,
		_font,
		connect_text,
		sanguis::gui::optional_needed_width(
			sanguis::gui::needed_width_from_strings(
				_font,
				sanguis::gui::string_container{
					connect_text,
					cancel_text
				}
			)
		)
	),
	connect_box_(
		gui_context_,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					hostname_line_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					port_line_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					connect_text_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					connect_button_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	connect_frame_(
		_renderer,
		connect_box_
	),
	quit_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Quit"),
		sanguis::gui::optional_needed_width()
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
					resolution_chooser_.widget()
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					player_name_line_
				),
				sge::rucksack::alignment::center
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					connect_frame_
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
	gui_area_(
		_renderer,
		_viewport_manager,
		main_container_
	),
	gui_master_(
		_keyboard,
		_cursor,
		gui_context_,
		gui_area_
	),
	gui_background_(
		_renderer,
		gui_area_,
		_textures.load(
			sanguis::client::load::resource::texture_identifier(
				FCPPT_TEXT("asphalt")
			)
		)
	),
	connect_running_{
		false
	},
	quickstart_connection_(
		quickstart_button_.click(
			std::bind(
				&sanguis::client::gui::menu::object::handle_quickstart,
				this
			)
		)
	),
	connect_connection_(
		connect_button_.click(
			std::bind(
				&sanguis::client::gui::menu::object::handle_connect,
				this
			)
		)
	),
	quit_connection_(
		quit_button_.click(
			callbacks_.quit()
		)
	),
	hostname_change_connection_(
		hostname_edit_.text_change(
			std::bind(
				&sanguis::client::gui::menu::object::handle_text_changed,
				this
			)
		)
	),
	port_change_connection_(
		port_edit_.text_change(
			std::bind(
				&sanguis::client::gui::menu::object::handle_text_changed,
				this
			)
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

	gui_master_.draw(
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

	typedef
	fcppt::optional<
		port_type
	>
	optional_port;

	optional_port const opt_port(
		fcppt::extract_from_string<
			port_type
		>(
			port_edit_.text()
		)
	);

	connect_button_.enable(
		opt_port
		&&
		!hostname_edit_.text().empty()
		&&
		(*opt_port > 0)
		&& (*opt_port < 65535)
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
