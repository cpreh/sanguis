#include "logic.hpp"
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
#include "../../cyclic_iterator_impl.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/console/object.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/text.hpp>
#include <algorithm>

sanguis::client::control::logic::logic(
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
	actions_(
		fcppt::assign::make_container<
			action_handlers
		>
		(
			std::tr1::bind(
				&logic::handle_move_x,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_move_y,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_rotation_x,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_rotation_y,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_shooting,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_switch_weapon_forwards,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_switch_weapon_backwards,
				this,
				std::tr1::placeholders::_1
			)
		)
		(
			std::tr1::bind(
				&logic::handle_escape,
				this,
				std::tr1::placeholders::_1
			)
		)
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
			FCPPT_TEXT("kill"),
			std::tr1::bind(
				&logic::send_cheat,
				this,
				cheat_type::kill,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			FCPPT_TEXT("Commit suicide")
		)
	),
	cheat_impulse_conn_(
		_console.insert(
			FCPPT_TEXT("impulse"),
			std::tr1::bind(
				&logic::send_cheat,
				this,
				cheat_type::impulse101,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			FCPPT_TEXT("Get all weapons")
		)
	),
	cheat_exp_conn_(
		_console.insert(
			FCPPT_TEXT("exp"),
			std::tr1::bind(
				&logic::send_cheat,
				this,
				cheat_type::exp,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			FCPPT_TEXT("Get a lot of exp")
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
sanguis::client::control::logic::handle_player_action(
	player_action const &_action
)
{
	actions_.at(
		_action.type()
	)(
		_action.scale()
	);
}

sanguis::client::control::logic::~logic()
{}

void
sanguis::client::control::logic::give_player_weapon(
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
		change_weapon(
			_weapon_type
		);
}

void
sanguis::client::control::logic::handle_move_x(
	key_scale const _scale
)
{
	environment_.direction_x(
		_scale
	);

	update_direction();
}

void
sanguis::client::control::logic::handle_move_y(
	key_scale const _scale
)
{
	environment_.direction_y(
		_scale
	);

	update_direction();
}

void
sanguis::client::control::logic::update_direction()
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
sanguis::client::control::logic::handle_rotation_x(
	key_scale const
)
{
	update_rotation();
}

void
sanguis::client::control::logic::handle_rotation_y(
	key_scale const
)
{
	update_rotation();
}

void
sanguis::client::control::logic::update_rotation()
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
sanguis::client::control::logic::handle_shooting(
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
sanguis::client::control::logic::handle_switch_weapon_forwards(
	key_scale
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

	typedef cyclic_iterator<
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

/*
	switch(m.type())
	{
	case player_action::switch_weapon_forwards:*/
		while(!*++it) ;
	/*
		break;
	case player_action::switch_weapon_backwards:
		while(!*--it) ;
		break;
	}
	*/

	change_weapon(
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
sanguis::client::control::logic::handle_switch_weapon_backwards(
	key_scale
)
{}

void
sanguis::client::control::logic::handle_escape(
	key_scale
)
{
}

void
sanguis::client::control::logic::change_weapon(
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
sanguis::client::control::logic::send_cheat(
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
