#include "logic.hpp"
#include "invalid_id.hpp"
#include "cursor/object.hpp"
#include "log.hpp"
#include "../messages/create.hpp"
#include "../messages/player_attack_dest.hpp"
#include "../messages/player_direction.hpp"
#include "../messages/player_rotation.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/player_pause.hpp"
#include "../messages/player_unpause.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../messages/player_choose_perk.hpp"
#include "../messages/player_cheat.hpp"
#include "../cyclic_iterator_impl.hpp"
#include "../perk_type.hpp"
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/vector/angle_between.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/resolution.hpp>
#include <sge/console/object.hpp>
#include <fcppt/log/headers.hpp>
#include <sge/gui/unit.hpp>
#include <sge/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <sge/optional_impl.hpp>
#include <fcppt/function/object.hpp>
#include <tr1/functional>
#include <algorithm>

sanguis::client::logic::logic(
	send_callback const &_send,
	sge::renderer::device_ptr const _rend,
	cursor::object_ptr const _cursor,
	sge::console::object &_console
)
:
	send(
		_send
	),
	rend(
		_rend
	),
	cursor_(_cursor),
	actions(
		sge::assign::make_container<
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
	player_id_(invalid_id),
	direction(
		direction_vector::null()
	),
	player_center(
		draw::sprite::point::null()
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

void sanguis::client::logic::handle_player_action(
	player_action const &action)
{
	if(player_id_ == invalid_id)
		return;
	
	actions.at(
		action.type()
	)(
		action.scale()
	);
}

sanguis::client::logic::~logic()
{}

void
sanguis::client::logic::give_weapon(
	messages::give_weapon const &m
)
{
	if(m.get<messages::roles::entity_id>() != player_id_)
	{
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Got invalid give_weapon message!")
		);

		return;
	}

	weapon_type::type const wt(
		static_cast<
			weapon_type::type
		>(
			m.get<messages::roles::weapon>()
		)
	);

	owned_weapons.at(wt) = true;

	// we don't own any weapon so take this one
	if(current_weapon == weapon_type::size)
		change_weapon(
			wt
		);
}

void sanguis::client::logic::move(
	messages::move const &m)
{
	if(m.get<messages::roles::entity_id>() == player_id_)
		player_center = fcppt::math::vector::structure_cast<
			draw::sprite::point
		>(
			m.get<messages::pos>()
		); // FIXME
}

void sanguis::client::logic::pause(
	bool const p)
{
	paused = p;
	cursor_->visible(
		paused);
}

void
sanguis::client::logic::remove(
	entity_id const id
)
{
	if(id == player_id_)
		player_id_ = invalid_id;
}

void
sanguis::client::logic::player_id(
	entity_id const id
)
{
	player_id_ = id;
}

sanguis::entity_id
sanguis::client::logic::player_id() const
{
	return player_id_;
}

void
sanguis::client::logic::handle_move_x(
	key_scale const s
)
{
	direction.x() += s;
	update_direction();
}

void
sanguis::client::logic::handle_move_y(
	key_scale const s
)
{
	direction.y() += s;
	update_direction();
}

void sanguis::client::logic::update_direction()
{
	send(
		messages::create(
			messages::player_direction(
				player_id_,
				fcppt::math::vector::structure_cast<
					messages::types::vector2
				>(
					direction
				)
			)
		)
	);
}

void sanguis::client::logic::handle_rotation_x(
	key_scale const s)
{
	update_rotation();
}

void sanguis::client::logic::handle_rotation_y(
	key_scale const s)
{
	update_rotation();
}

void sanguis::client::logic::update_rotation()
{
	sge::optional<
		messages::types::space_unit
	> const rotation(
		fcppt::math::vector::angle_between<
			messages::types::space_unit
		>(
			player_center,
			cursor_->pos()
		)
	);

	if(!rotation || !rotation_timer.update_b())
		return;
	
	// TODO: maybe we can kick rotation
	// and the server can calculate it from the attack dest
	send(
		messages::create(
			messages::player_rotation(
				player_id_,
				*rotation
			)
		)
	);


	send(
		messages::create(
			messages::player_attack_dest(
				player_id_,
				fcppt::math::vector::structure_cast<
					messages::types::vector2
				>(
					cursor_->pos()
				)
			)
		)
	);

}

void sanguis::client::logic::handle_shooting(
	key_scale const s)
{
	if(
		fcppt::math::compare(
			static_cast<key_scale>(0),
			s
		)
	)
		send(
			messages::create(
				messages::player_stop_shooting(
					player_id_
				)
			)
		);
	else
		send(
			messages::create(
				messages::player_start_shooting(
					player_id_
				)
			)
		);
}

void sanguis::client::logic::handle_switch_weapon_forwards(
	key_scale)
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

	//switch(m.type()) {
	//case player_action::switch_weapon_forwards:
		while(!*++it) ;
	//	break;
	/*case player_action::switch_weapon_backwards:
		while(!*--it) ;
		break;
	default:
		return;
	}*/

	change_weapon(
		static_cast<weapon_type::type>(
			std::distance(
				static_cast<owned_weapons_array const &>(
					owned_weapons
				).begin(),
				it.get()
			)
		)
	);
}

void sanguis::client::logic::handle_switch_weapon_backwards(
	key_scale)
{}

void sanguis::client::logic::handle_pause_unpause(
	key_scale)
{
	if(paused)
		send(
			messages::create(
				messages::player_unpause(
					player_id_
				)
			)
		);
	else
		send(
			messages::create(
				messages::player_pause(
					player_id_
				)
			)
		);
}

void sanguis::client::logic::change_weapon(
	weapon_type::type const w)
{
	current_weapon = w;

	send(
		messages::create(
			messages::player_change_weapon(
				player_id_,
				current_weapon
			)
		)
	);
}

void sanguis::client::logic::send_cheat(
	cheat_type::type const c)
{
	send(
		messages::create(
			messages::player_cheat(
				player_id_,
				c
			)
		)
	);
}
