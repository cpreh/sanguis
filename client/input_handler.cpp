#include "input_handler.hpp"
#include "player_action.hpp"

#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/iostream.hpp>

sanguis::client::input_handler::input_handler(
	const post_fun& post_message)
: post_message(post_message),
  last_x(0),
  last_y(0)
{}

void sanguis::client::input_handler::input_callback(const sge::key_pair& p)
{
	const sge::key_code code = p.key().code();
	switch(code) {
	case sge::kc::key_left:
	case sge::kc::key_right:
	case sge::kc::key_up:
	case sge::kc::key_down:
		direction_event(p);
		break;
	case sge::kc::mouse_x_axis:
	case sge::kc::mouse_y_axis:
		rotation_event(p);
		break;
	default:
		break;
	}
}

void sanguis::client::input_handler::direction_event(const sge::key_pair& p)
{
	const sge::key_state val(p.value() ? 1 : -1);

	player_action::action_type to_send;
	key_scale scale = static_cast<key_scale>(val);

	switch(p.key().code()) {
	case sge::kc::key_left:
		scale = -scale;
	case sge::kc::key_right:
		to_send = player_action::horizontal_move;
		break;
	case sge::kc::key_up:
		scale = -scale;
	case sge::kc::key_down:
		to_send = player_action::vertical_move;
		break;
	default:
		throw sge::exception(SGE_TEXT("direction_event: impossible!"));
	}
	post_message(player_action(to_send, scale));
}

#include <sge/iostream.hpp>
#include <ostream>

void sanguis::client::input_handler::rotation_event(const sge::key_pair& p)
{
	player_action::action_type to_send;

	switch(p.key().code()) {
	case sge::kc::mouse_x_axis:
		to_send = player_action::horizontal_look;
		break;
	case sge::kc::mouse_y_axis:
		to_send = player_action::vertical_look;
		break;
	default:
		throw sge::exception(SGE_TEXT("rotation_event: impossible!"));
	}

	post_message(player_action(to_send, static_cast<key_scale>(p.value())));
}
