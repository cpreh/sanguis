#include "action_handler.hpp"
#include "player_action.hpp"
#include "environment.hpp"
#include "../log.hpp"
#include "../../messages/create.hpp"
#include "../../messages/player_attack_dest.hpp"
#include "../../messages/player_direction.hpp"
#include "../../messages/player_rotation.hpp"
#include "../../messages/player_start_shooting.hpp"
#include "../../messages/player_stop_shooting.hpp"
#include "../../messages/player_change_weapon.hpp"
#include "../../messages/player_cheat.hpp"
#include "../../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/console/object.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/cyclic_iterator.hpp>
#include <fcppt/text.hpp>
#include <algorithm>
#include <iterator>

sanguis::client::control::action_handler::action_handler(
	send_callback const &_send,
	control::environment &_environment,
	sge::console::object &_console
)
:
	send_(
		_send
	),
	environment_(
		_environment
	),
	current_weapon_(
		weapon_type::size
	),
	rotation_timer_(
		sge::time::millisecond(
			100
		)
	),
	owned_weapons_(),
	cheat_kill_conn_(
		_console.insert(
			SGE_FONT_TEXT_LIT("kill"),
			std::tr1::bind(
				&action_handler::send_cheat,
				this,
				cheat_type::kill,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			SGE_FONT_TEXT_LIT("Commit suicide")
		)
	),
	cheat_impulse_conn_(
		_console.insert(
			SGE_FONT_TEXT_LIT("impulse"),
			std::tr1::bind(
				&action_handler::send_cheat,
				this,
				cheat_type::impulse101,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			SGE_FONT_TEXT_LIT("Get all weapons")
		)
	),
	cheat_exp_conn_(
		_console.insert(
			SGE_FONT_TEXT_LIT("exp"),
			std::tr1::bind(
				&action_handler::send_cheat,
				this,
				cheat_type::exp,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			SGE_FONT_TEXT_LIT("Get a lot of exp")
		)
	)
{
	std::fill(
		owned_weapons_.begin(),
		owned_weapons_.end(),
		false
	);
}

void
sanguis::client::control::action_handler::handle_player_action(
	player_action const &_action
)
{
	key_scale const scale(
		_action.scale()
	);

	switch(
		_action.type()
	)
	{
	case action_type::horizontal_move:
		this->handle_move_x(
			scale
		);

		return;
	case action_type::vertical_move:
		this->handle_move_y(
			scale
		);

		return;
	case action_type::horizontal_look:
	case action_type::vertical_look:
		this->update_rotation();

		return;
	case action_type::shoot:
		this->handle_shooting(
			scale
		);

		return;
	case action_type::switch_weapon_forwards:
		this->handle_switch_weapon(
			true
		);

		return;
	case action_type::switch_weapon_backwards:
		this->handle_switch_weapon(
			false
		);

		return;
	case action_type::perk_menu:
	case action_type::escape:
		throw sanguis::exception(
			FCPPT_TEXT("Invalid action in action_handler!")
		);
	}
}

sanguis::client::control::action_handler::~action_handler()
{}

void
sanguis::client::control::action_handler::give_player_weapon(
	weapon_type::type const _weapon_type
)
{
	owned_weapons_.at(
		_weapon_type
	) = true;

	// we don't own any weapon so take this one
	if(
		current_weapon_ == weapon_type::size
	)
		this->change_weapon(
			_weapon_type
		);
}

void
sanguis::client::control::action_handler::handle_move_x(
	key_scale const _scale
)
{
	environment_.direction_x(
		_scale
	);

	this->update_direction();
}

void
sanguis::client::control::action_handler::handle_move_y(
	key_scale const _scale
)
{
	environment_.direction_y(
		_scale
	);

	this->update_direction();
}

void
sanguis::client::control::action_handler::update_direction()
{
	send_(
		sanguis::messages::create(
			sanguis::messages::player_direction(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
				>(
					environment_.direction()
				)
			)
		)
	);
}

void
sanguis::client::control::action_handler::update_rotation()
{
	// FIXME: the rotation is still handled in the cursor

	if(
		!rotation_timer_.update_b()
	)
		return;
	
	// TODO: maybe we can kick rotation
	// and the server can calculate it from the attack dest
	send_(
		sanguis::messages::create(
			sanguis::messages::player_rotation(
				environment_.rotation()
			)
		)
	);

	send_(
		sanguis::messages::create(
			sanguis::messages::player_attack_dest(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
				>(
					environment_.attack_dest()
				)
			)
		)
	);
}

void
sanguis::client::control::action_handler::handle_shooting(
	key_scale const _scale
)
{
	if(
		fcppt::math::almost_zero(
			_scale
		)
	)
		send_(
			sanguis::messages::create(
				sanguis::messages::player_stop_shooting()
			)
		);
	else
		send_(
			sanguis::messages::create(
				sanguis::messages::player_start_shooting()
			)
		);
}

void
sanguis::client::control::action_handler::handle_switch_weapon(
	bool const _forward
)
{
	// we don't own any weapon
	if(
		current_weapon_ == weapon_type::size
	)
		return;

	owned_weapons_array::size_type const weapon_index(
		static_cast<
			owned_weapons_array::size_type
		>(
			current_weapon_
		)
	);

	FCPPT_ASSERT(
		weapon_index < owned_weapons_.size()
	);

	typedef fcppt::cyclic_iterator<
		owned_weapons_array::const_iterator
	> iterator;
	
	iterator it(
		owned_weapons_.begin()
		+ static_cast<
			owned_weapons_array::size_type
		>(
			current_weapon_
		),
		owned_weapons_.begin(),
		owned_weapons_.end()
	);

	if(
		_forward
	)
		while(!*++it) ;
	else
		while(!*--it) ;

	this->change_weapon(
		static_cast<
			weapon_type::type
		>(
			std::distance(
				static_cast<
					owned_weapons_array const &
				>(
					owned_weapons_
				).begin(),
				it.get()
			)
		)
	);
}

void
sanguis::client::control::action_handler::change_weapon(
	weapon_type::type const _weapon_type
)
{
	current_weapon_ = _weapon_type;

	send_(
		sanguis::messages::create(
			sanguis::messages::player_change_weapon(
				current_weapon_
			)
		)
	);
}

void
sanguis::client::control::action_handler::send_cheat(
	cheat_type::type const _cheat,
	sge::console::arg_list const &,
	sge::console::object &
)
{
	send_(
		sanguis::messages::create(
			sanguis::messages::player_cheat(
				_cheat
			)
		)
	);
}
