#include "input_handler.hpp"
#include "player_action.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

sanguis::client::control::input_handler::input_handler(
	sge::input::system_ptr const _input_sys,
	post_fun const &_post_message
)
:
	active_(false),
	post_message_(_post_message),
	connection_(
		_input_sys->register_callback(
			std::tr1::bind(
				&input_handler::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	last_x_(0),
	last_y_(0)
{}

void
sanguis::client::control::input_handler::active(
	bool const _active
)
{
	if(
		active_ == _active
	)
	{
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("input_active ")
				<< (
					!_active
					?
						FCPPT_TEXT("unset")
					:
						FCPPT_TEXT("set")
				)
				<< FCPPT_TEXT(" twice!")
		);
	}

	active_ = _active;
}

void
sanguis::client::control::input_handler::input_callback(
	sge::input::key_pair const &_key_pair
)
{
	if(!active_)
		return;

	sge::input::key_code const code(
		_key_pair.key().code()
	);

	switch(
		code
	)
	{
	case sge::input::kc::key_a:
	case sge::input::kc::key_d:
	case sge::input::kc::key_w:
	case sge::input::kc::key_s:
		direction_event(
			_key_pair
		);
		break;
	case sge::input::kc::mouse_x_axis:
	case sge::input::kc::mouse_y_axis:
		rotation_event(
			_key_pair
		);
		break;
	case sge::input::kc::mouse_l:
		shooting_event(
			_key_pair
		);
		break;
	case sge::input::kc::key_x:
	case sge::input::kc::key_c:
		weapon_switch_event(
			_key_pair
		);
		break;
	case sge::input::kc::key_e:
		pause_unpause_event(
			_key_pair
		);
		break;
	default:
		break;
	}
}

void
sanguis::client::control::input_handler::direction_event(
	sge::input::key_pair const &_key_pair
)
{
	// TODO: fix this!
	sge::input::key_state const val(
		_key_pair.value()
		?
			1
		:
			-1
	);

	action_type::type to_send;

	key_scale scale = static_cast<key_scale>(val);

	switch(_key_pair.key().code()) {
	case sge::input::kc::key_a:
		scale = -scale;
	case sge::input::kc::key_d:
		to_send = action_type::horizontal_move;
		break;
	case sge::input::kc::key_w:
		scale = -scale;
	case sge::input::kc::key_s:
		to_send = action_type::vertical_move;
		break;
	default:
		throw exception(
			FCPPT_TEXT("direction_event: impossible!")
		);
	}

	post_message_(
		player_action(
			to_send,
			scale
		)
	);
}

void
sanguis::client::control::input_handler::rotation_event(
	sge::input::key_pair const &_key_pair
)
{
	action_type::type to_send;

	switch(
		_key_pair.key().code()
	)
	{
	case sge::input::kc::mouse_x_axis:
		to_send = action_type::horizontal_look;
		break;
	case sge::input::kc::mouse_y_axis:
		to_send = action_type::vertical_look;
		break;
	default:
		throw exception(
			FCPPT_TEXT("rotation_event: impossible!")
		);
	}

	post_message_(
		player_action(
			to_send,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}

void
sanguis::client::control::input_handler::shooting_event(
	sge::input::key_pair const &_key_pair
)
{
	post_message_(
		player_action(
			action_type::shoot,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}
	
void
sanguis::client::control::input_handler::weapon_switch_event(
	sge::input::key_pair const &_key_pair
)
{
	if(
		!_key_pair.value()
	)
		return;

	post_message_(
		player_action(
			_key_pair.key().code() == sge::input::kc::key_x
			?
				action_type::switch_weapon_backwards
			:
				action_type::switch_weapon_forwards,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}

void
sanguis::client::control::input_handler::pause_unpause_event(
	sge::input::key_pair const &_key_pair
)
{
	if(
		!_key_pair.value()
	)
		return;

	post_message_(
		player_action(
			action_type::pause_unpause,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}
