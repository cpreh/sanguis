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
#include "../../messages/player_pause.hpp"
#include "../../messages/player_unpause.hpp"
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
	environment &environment_,
	sge::console::object &_console
)
:
	send(
		_send
	),
	environment_(environment_),
	actions(
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
				&logic::handle_pause_unpause,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	current_weapon(
		weapon_type::size
	),
	paused(false),
	rotation_timer(
		sge::time::millisecond(
			100
		)
	),
	owned_weapons(),
	cheat_kill_conn_(
		_console.insert(
			FCPPT_TEXT("kill"),
			std::tr1::bind(
				&logic::send_cheat,
				this,
				cheat_type::kill
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
				cheat_type::impulse101
			),
			FCPPT_TEXT("Get all weapons")
		)
	)

{
	std::fill(
		owned_weapons.begin(),
		owned_weapons.end(),
		false
	);
}

void
sanguis::client::control::logic::handle_player_action(
	player_action const &action
)
{
	actions.at(
		action.type()
	)(
		action.scale()
	);
}

sanguis::client::control::logic::~logic()
{}

void
sanguis::client::control::logic::give_player_weapon(
	weapon_type::type const wt
)
{
	owned_weapons.at(
		wt
	) = true;

	// we don't own any weapon so take this one
	if(current_weapon == weapon_type::size)
		change_weapon(
			wt
		);
}

void
sanguis::client::control::logic::pause(
	bool const p
)
{
	paused = p;
}

void
sanguis::client::control::logic::handle_move_x(
	key_scale const s
)
{
	environment_.direction_x(
		s
	);

	update_direction();
}

void
sanguis::client::control::logic::handle_move_y(
	key_scale const s
)
{
	environment_.direction_y(
		s
	);

	update_direction();
}

void
sanguis::client::control::logic::update_direction()
{
	send(
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

	if(!rotation_timer.update_b())
		return;
	
	// TODO: maybe we can kick rotation
	// and the server can calculate it from the attack dest
	send(
		sanguis::messages::create(
			sanguis::messages::player_rotation(
				environment_.rotation()
			)
		)
	);

	send(
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
	key_scale const s
)
{
	if(
		fcppt::math::almost_zero(
			s
		)
	)
		send(
			sanguis::messages::create(
				sanguis::messages::player_stop_shooting()
			)
		);
	else
		send(
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
	if(current_weapon == weapon_type::size)
		return;

	owned_weapons_array::size_type const weapon_index(
		static_cast<owned_weapons_array::size_type>(
			current_weapon
		)
	);

	FCPPT_ASSERT(weapon_index < owned_weapons.size());

	cyclic_iterator<
		owned_weapons_array::const_iterator
	> it(
		owned_weapons.begin()
		+ static_cast<owned_weapons_array::size_type>(current_weapon),
		owned_weapons.begin(),
		owned_weapons.end()
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
					owned_weapons
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
sanguis::client::control::logic::handle_pause_unpause(
	key_scale
)
{
	if(paused)
		send(
			sanguis::messages::create(
				sanguis::messages::player_unpause()
			)
		);
	else
		send(
			sanguis::messages::create(
				sanguis::messages::player_pause()
			)
		);
}

void
sanguis::client::control::logic::change_weapon(
	weapon_type::type const w
)
{
	current_weapon = w;

	send(
		sanguis::messages::create(
			sanguis::messages::player_change_weapon(
				current_weapon
			)
		)
	);
}

void
sanguis::client::control::logic::send_cheat(
	cheat_type::type const c
)
{
	send(
		sanguis::messages::create(
			sanguis::messages::player_cheat(
				c
			)
		)
	);
}
