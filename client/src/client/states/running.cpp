#include <sanguis/magazine_remaining.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/client/cursor.hpp>
#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager.hpp>
#include <sanguis/client/weapon_description_from_message.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/control/input_translator.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/hud/object.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/messages/call/forward_to_default.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <sanguis/messages/roles/console_message.hpp>
#include <sanguis/messages/roles/exp_for_next_level.hpp>
#include <sanguis/messages/roles/experience.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/level.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
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
#include <sanguis/messages/server/remove_weapon.hpp>
#include <sanguis/messages/server/unpause.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/console/object.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/input/cursor/activatable_fwd.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::running::running(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	hud_resources_(
		this->context<
			sanguis::client::machine
		>().resources().resources().textures()
	),
	console_(
		fcppt::make_unique_ptr<
			sanguis::client::console::object
		>(
			this->context<
				sanguis::client::machine
			>().console_gfx(),
			sanguis::client::make_send_callback(
				this->context<
					sanguis::client::machine
				>()
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
			hud_resources_,
			this->context<
				sanguis::client::machine
			>().gui_style(),
			this->context<
				sanguis::client::machine
			>().font_object(),
			this->context<
				sanguis::client::machine
			>().renderer(),
			this->context<
				sanguis::client::machine
			>().viewport_manager(),
			this->context<
				sanguis::client::machine
			>().keyboard(),
			this->context<
				sanguis::client::machine
			>().cursor()
		)
	),
	drawer_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::object
		>(
			this->context<
				sanguis::client::machine
			>().resources(),
			hud_resources_,
			*sound_manager_,
			this->context<
				sanguis::client::machine
			>().gui_style(),
			this->context<
				sanguis::client::machine
			>().renderer(),
			this->context<
				sanguis::client::machine
			>().font_object(),
			this->context<
				sanguis::client::machine
			>().viewport_manager(),
			sanguis::client::player_health_callback(
				std::bind(
					&sanguis::client::gui::hud::object::health_pair,
					hud_.get(),
					std::placeholders::_1
				)
			)
		)
	),
	input_translator_(
		fcppt::make_unique_ptr<
			sanguis::client::control::input_translator
		>(
			this->context<
				sanguis::client::machine
			>().keyboard(),
			this->context<
				sanguis::client::machine
			>().cursor(),
			std::bind(
				&sanguis::client::states::running::handle_player_action,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::client::states::running::~running()
{
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::tick const &_event
)
{
	drawer_->update(
		_event.delta()
	);

	hud_->update(
		_event.delta()
	);

	sound_manager_->update();

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
			_event.context()
		)
	);

	// TODO: Put this in draw2d
	this->context<
		sanguis::client::machine
	>().cursor_gfx().draw(
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
			boost::mpl::vector11<
				sanguis::messages::server::add_console_command,
				sanguis::messages::server::add_own_player,
				sanguis::messages::server::change_world,
				sanguis::messages::server::console_print,
				sanguis::messages::server::experience,
				sanguis::messages::server::give_weapon,
				sanguis::messages::server::level_up,
				sanguis::messages::server::magazine_remaining,
				sanguis::messages::server::pause,
				sanguis::messages::server::remove_weapon,
				sanguis::messages::server::unpause
			>
		>(
			*this,
			_event,
			handle_default_msg
		);
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::net_error const &_error
)
{
	return
		this->transit<
			sanguis::client::states::menu
		>();
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::add_console_command const &_message
)
{
	fcppt::string const
		name(
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::command_name
				>()
			)
		),
		description(
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::command_description
				>()
			)
		);

	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Got a new console command: \"")
			<< name
			<< FCPPT_TEXT("\", description: \"")
			<< description
			<< FCPPT_TEXT('"')
	);

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
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::name
				>()
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
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::world_name
				>()
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
		sge::font::from_fcppt_string(
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::console_message
				>()
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
			_message.get<
				sanguis::messages::roles::experience
			>()
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
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::running::operator()(
	sanguis::messages::server::magazine_remaining const &_message
)
{
	hud_->magazine_remaining(
		_message.get<
			sanguis::messages::roles::is_primary_weapon
		>(),
		sanguis::magazine_remaining(
			_message.get<
				sanguis::messages::roles::magazine_remaining
			>()
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
			_message.get<
				sanguis::messages::roles::level
			>()
		),
		sanguis::client::exp_for_next_level(
			_message.get<
				sanguis::messages::roles::exp_for_next_level
			>()
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
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
	sanguis::messages::server::remove_weapon const &_message
)
{
	hud_->remove_weapon(
		_message.get<
			sanguis::messages::roles::is_primary_weapon
		>()
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

sanguis::client::control::environment &
sanguis::client::states::running::control_environment()
{
	return
		drawer_->control_environment();
}

sanguis::client::console::object &
sanguis::client::states::running::console()
{
	return
		*console_;
}

sge::input::cursor::activatable &
sanguis::client::states::running::cursor()
{
	return
		input_translator_->cursor();
}

sanguis::client::gui::hud::object &
sanguis::client::states::running::hud_gui()
{
	return
		*hud_;
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
}
