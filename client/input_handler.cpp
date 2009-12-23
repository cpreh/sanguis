#include "input_handler.hpp"
#include "player_action.hpp"
#include "../exception.hpp"
#include <sge/input/key_pair.hpp>
#include <fcppt/text.hpp>

sanguis::client::input_handler::input_handler(
	post_fun const &post_message)
:
	post_message(post_message),
	last_x(0),
	last_y(0)
{}

void sanguis::client::input_handler::input_callback(
	sge::input::key_pair const &p)
{
	sge::input::key_code const code = p.key().code();
	switch(code) {
	case sge::input::kc::key_a:
	case sge::input::kc::key_d:
	case sge::input::kc::key_w:
	case sge::input::kc::key_s:
		direction_event(p);
		break;
	case sge::input::kc::mouse_x_axis:
	case sge::input::kc::mouse_y_axis:
		rotation_event(p);
		break;
	case sge::input::kc::mouse_l:
		shooting_event(p);
		break;
	case sge::input::kc::key_x:
	case sge::input::kc::key_c:
		weapon_switch_event(p);
		break;
	case sge::input::kc::key_e:
		pause_unpause_event(p);
		break;
	default:
		break;
	}
}

void sanguis::client::input_handler::direction_event(
	sge::input::key_pair const &p)
{
	sge::input::key_state const val(
		p.value() ? 1 : -1);

	player_action::action_type to_send;
	key_scale scale = static_cast<key_scale>(val);

	switch(p.key().code()) {
	case sge::input::kc::key_a:
		scale = -scale;
	case sge::input::kc::key_d:
		to_send = player_action::horizontal_move;
		break;
	case sge::input::kc::key_w:
		scale = -scale;
	case sge::input::kc::key_s:
		to_send = player_action::vertical_move;
		break;
	default:
		throw exception(
			FCPPT_TEXT("direction_event: impossible!")
		);
	}

	post_message(
		player_action(
			to_send,
			scale
		)
	);
}

void sanguis::client::input_handler::rotation_event(
	sge::input::key_pair const &p)
{
	player_action::action_type to_send;

	switch(p.key().code()) {
	case sge::input::kc::mouse_x_axis:
		to_send = player_action::horizontal_look;
		break;
	case sge::input::kc::mouse_y_axis:
		to_send = player_action::vertical_look;
		break;
	default:
		throw exception(
			FCPPT_TEXT("rotation_event: impossible!")
		);
	}

	post_message(
		player_action(
			to_send,
			static_cast<key_scale>(
				p.value()
			)
		)
	);
}

void sanguis::client::input_handler::shooting_event(
	sge::input::key_pair const &p)
{
	post_message(
		player_action(
			player_action::shoot,
			static_cast<key_scale>(
				p.value()
			)
		)
	);
}
	
void sanguis::client::input_handler::weapon_switch_event(
	sge::input::key_pair const &p)
{
	if(!p.value())
		return;
	post_message(
		player_action(
			p.key().code() == sge::input::kc::key_x
			? player_action::switch_weapon_backwards
			: player_action::switch_weapon_forwards,
			static_cast<key_scale>(
				p.value()
			)
		)
	);
}

void sanguis::client::input_handler::pause_unpause_event(
	sge::input::key_pair const &p)
{
	if(!p.value())
		return;
	post_message(
		player_action(
			player_action::pause_unpause,
			static_cast<key_scale>(
				p.value()
			)
		)
	);
}
