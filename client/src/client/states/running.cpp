#include <sanguis/exception.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/dispatch_default_function.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/optional_health_pair_fwd.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/sound_manager.hpp>
#include <sanguis/client/weapon_description_from_message.hpp>
#include <sanguis/client/args/labels/draw_debug.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/input_translator.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/control/actions/callback.hpp>
#include <sanguis/client/draw/base.hpp>
#include <sanguis/client/draw2d/create.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/hud/object.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/messages/call/forward_to_default.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <sanguis/messages/roles/console_message.hpp>
#include <sanguis/messages/roles/exp_for_next_level.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/level.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/roles/slowdown.hpp>
#include <sanguis/messages/roles/world_name.hpp>
#include <sanguis/messages/server/add_console_command.hpp>
#include <sanguis/messages/server/add_own_player.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/change_world.hpp>
#include <sanguis/messages/server/console_print.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/experience.hpp>
#include <sanguis/messages/server/give_weapon.hpp>
#include <sanguis/messages/server/level_up.hpp>
#include <sanguis/messages/server/magazine_remaining.hpp>
#include <sanguis/messages/server/pause.hpp>
#include <sanguis/messages/server/reload.hpp>
#include <sanguis/messages/server/remove_weapon.hpp>
#include <sanguis/messages/server/slowdown.hpp>
#include <sanguis/messages/server/unpause.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/console/object.hpp>
#include <sge/font/from_std_wstring.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::states::running::running(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	log_{
		this->context<
			sanguis::client::machine
		>().log_context(),
		sanguis::client::states::log_location(),
		fcppt::log::parameters_no_function(
			fcppt::log::name{
				FCPPT_TEXT("running")
			}
		)
	},
	hud_resources_(
		this->context<
			sanguis::client::machine
		>().log_context(),
		fcppt::make_cref(
			this->context<
				sanguis::client::machine
			>().resources().resources().textures()
		)
	),
	console_(
		fcppt::make_unique_ptr<
			sanguis::client::console::object
		>(
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().console_gfx()
			),
			sanguis::client::make_send_callback(
				fcppt::make_ref(
					this->context<
						sanguis::client::machine
					>()
				)
			)
		)
	),
	sound_manager_(
		fcppt::make_unique_ptr<
			sanguis::client::sound_manager
		>()
	),
	hud_(
		fcppt::make_unique_ptr<
			sanguis::client::gui::hud::object
		>(
			fcppt::make_ref(
				hud_resources_
			),
			fcppt::make_cref(
				this->context<
					sanguis::client::machine
				>().gui_style()
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().font_object()
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().renderer()
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().viewport_manager()
			)
		)
	),
	drawer_(
		sanguis::client::draw2d::create(
			this->context<
				sanguis::client::machine
			>().log_context(),
			fcppt::make_cref(
				this->context<
					sanguis::client::machine
				>().resources()
			),
			fcppt::make_ref(
				hud_resources_
			),
			fcppt::make_ref(
				*sound_manager_
			),
			fcppt::make_cref(
				this->context<
					sanguis::client::machine
				>().gui_style()
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().renderer()
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().font_object()
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().viewport_manager()
			),
			sanguis::client::player_health_callback(
				[
					this
				](
					sanguis::client::optional_health_pair const &_health
				)
				{
					this->hud_->health_pair(
						_health
					);
				}
			),
			fcppt::make_ref(
				this->context<
					sanguis::client::machine
				>().cursor_gfx()
			),
			fcppt::record::get<
				sanguis::client::args::labels::draw_debug
			>(
				this->context<
					sanguis::client::machine
				>().options()
			)
		)
	),
	input_translator_(
		fcppt::make_unique_ptr<
			sanguis::client::control::input_translator
		>(
			sanguis::client::control::actions::callback{
				[
					this
				](
					sanguis::client::control::actions::any const &_action
				)
				{
					this->handle_player_action(
						_action
					);
				}
			}
		)
	),
	slowdown_{
		fcppt::literal<
			sanguis::slowdown::value_type
		>(
			1
		)
	}
{
}

FCPPT_PP_POP_WARNING

sanguis::client::states::running::~running()
= default;

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::tick const &_event
)
{
	this->update(
		_event,
		sanguis::client::control::optional_cursor_position()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::render const &_event
)
{
	drawer_->draw(
		_event.context()
	);

	hud_->draw(
		_event.context()
	);

	this->post_event(
		sanguis::client::events::overlay(
			fcppt::make_ref(
				_event.context()
			)
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::overlay const &_event
)
{
	drawer_->overlay(
		_event.context()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::message const &_event
)
{
	auto const handle_default_msg(
		[
			this
		](
			sanguis::messages::server::base const &_message
		)
		{
			drawer_->process_message(
				_message
			);

			return
				this->discard_event();
		}
	);

	return
		sanguis::client::dispatch<
			metal::list<
				sanguis::messages::server::add_console_command,
				sanguis::messages::server::add_own_player,
				sanguis::messages::server::change_world,
				sanguis::messages::server::console_print,
				sanguis::messages::server::experience,
				sanguis::messages::server::give_weapon,
				sanguis::messages::server::level_up,
				sanguis::messages::server::magazine_remaining,
				sanguis::messages::server::pause,
				sanguis::messages::server::reload,
				sanguis::messages::server::remove_weapon,
				sanguis::messages::server::slowdown,
				sanguis::messages::server::unpause
			>
		>(
			*this,
			_event,
			sanguis::client::dispatch_default_function{
				handle_default_msg
			}
		);
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::net_error const &_error
)
{
	this->post_event(
		_error
	);

	return
		this->transit<
			sanguis::client::states::menu
		>();
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::input const &_input
)
{
	input_translator_->on_event(
		_input.get()
	);

	return
		this->discard_event();
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::add_console_command const &_message
)
{
	fcppt::string const name(
		fcppt::optional::to_exception(
			sge::charconv::utf8_string_to_fcppt(
				fcppt::record::get<
					sanguis::messages::roles::command_name
				>(
					_message.get()
				)
			),
			[]{
				return
					sanguis::exception{
						FCPPT_TEXT("Failed to convert command name!")
					};
			}
		)
	);

	fcppt::string const description(
		fcppt::optional::to_exception(
			sge::charconv::utf8_string_to_fcppt(
				fcppt::record::get<
					sanguis::messages::roles::command_description
				>(
					_message.get()
				)
			),
			[]{
				return
					sanguis::exception{
						FCPPT_TEXT("Failed to convert command description!")
					};
			}
		)
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("Got a new console command: \"")
			<< name
			<< FCPPT_TEXT("\", description: \"")
			<< description
			<< FCPPT_TEXT('"')
	)

	console_->register_server_command(
		name,
		description
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::add_own_player const &_message
)
{
	hud_->player_name(
		sanguis::player_name(
			// FIXME
			fcppt::optional::to_exception(
				sge::charconv::utf8_string_to_fcppt(
					fcppt::record::get<
						sanguis::messages::roles::name
					>(
						_message.get()
					)
				),
				[]{
					return
						sanguis::exception{
							FCPPT_TEXT("Failed to convert player name!")
						};
				}
			)
		)
	);

	return
		sanguis::messages::call::result(
			sanguis::messages::call::forward_to_default()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::change_world const &_message
)
{
	hud_->world_name(
		sanguis::world_name(
			fcppt::optional::to_exception(
				sge::charconv::utf8_string_to_fcppt(
					fcppt::record::get<
						sanguis::messages::roles::world_name
					>(
						_message.get()
					)
				),
				[]{
					return
						sanguis::exception{
							FCPPT_TEXT("Failed to convert world name!")
						};
				}
			)
		)
	);

	return
		sanguis::messages::call::result(
			sanguis::messages::call::forward_to_default()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::console_print const &_message
)
{
	console_->sge_console().emit_message(
		sge::font::from_std_wstring(
			sge::charconv::convert<
				sge::charconv::encoding::wchar,
				sge::charconv::encoding::utf8
			>(
				fcppt::record::get<
					sanguis::messages::roles::console_message
				>(
					_message.get()
				)
			)
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::experience const &_message
)
{
	hud_->experience(
		sanguis::client::exp(
			_message.get()
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::give_weapon const &_message
)
{
	hud_->add_weapon(
		sanguis::client::weapon_description_from_message(
			_message
		)
	);

	return
		sanguis::messages::call::result(
			sanguis::messages::call::forward_to_default()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::magazine_remaining const &_message
)
{
	hud_->magazine_remaining(
		fcppt::record::get<
			sanguis::messages::roles::is_primary_weapon
		>(
			_message.get()
		),
		sanguis::magazine_remaining(
			fcppt::record::get<
				sanguis::messages::roles::magazine_remaining
			>(
				_message.get()
			)
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::level_up const &_message
)
{
	hud_->level(
		sanguis::client::level(
			fcppt::record::get<
				sanguis::messages::roles::level
			>(
				_message.get()
			)
		),
		sanguis::client::exp_for_next_level(
			fcppt::record::get<
				sanguis::messages::roles::exp_for_next_level
			>(
				_message.get()
			)
		)
	);

	return
		sanguis::messages::call::result(
			sanguis::messages::call::forward_to_default()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::pause const &
)
{
	this->do_pause(
		true
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::reload const &_message
)
{
	hud_->reload_time(
		fcppt::record::get<
			sanguis::messages::roles::is_primary_weapon
		>(
			_message.get()
		),
		fcppt::record::get<
			sanguis::messages::roles::reload_time
		>(
			_message.get()
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::remove_weapon const &_message
)
{
	hud_->remove_weapon(
		_message.get()
	);

	return
		sanguis::messages::call::result(
			sanguis::messages::call::forward_to_default()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::slowdown const &_message
)
{
	slowdown_ =
		sanguis::slowdown{
			fcppt::record::get<
				sanguis::messages::roles::slowdown
			>(
				_message.get()
			)
		};

	FCPPT_ASSERT_ERROR(
		slowdown_
		>
		sanguis::slowdown{
			0.F
		}
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::unpause const &
)
{
	this->do_pause(
		false
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::client::console::object &
sanguis::client::states::running::console()
{
	return
		*console_;
}

sanguis::client::gui::hud::object &
sanguis::client::states::running::hud_gui()
{
	return
		*hud_;
}

sanguis::client::control::environment const &
sanguis::client::states::running::control_environment() const
{
	return
		*drawer_;
}

void
sanguis::client::states::running::update(
	sanguis::client::events::tick const &_event,
	sanguis::client::control::optional_cursor_position const &_cursor_position
)
{
	sanguis::client::slowed_duration const slowed_duration{
		_event.delta()
		/
		slowdown_.get()
	};

	drawer_->update(
		slowed_duration,
		_cursor_position
	);

	hud_->update(
		_event.delta()
	);

	hud_->update_server(
		slowed_duration
	);

	sound_manager_->update();
}

void
sanguis::client::states::running::handle_player_action(
	sanguis::client::control::actions::any const &_action
)
{
	this->post_event(
		sanguis::client::events::action(
			_action
		)
	);
}

void
sanguis::client::states::running::do_pause(
	bool const _pause
)
{
	drawer_->pause(
		_pause
	);

	sound_manager_->pause(
		_pause
	);

	hud_->pause(
		_pause
	);
}
