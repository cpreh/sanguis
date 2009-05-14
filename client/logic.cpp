#include "logic.hpp"
#include "invalid_id.hpp"
#include "log.hpp"
#include "cursor.hpp"
#include "../messages/create.hpp"
#include "../messages/player_direction.hpp"
#include "../messages/player_rotation.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/player_pause.hpp"
#include "../messages/player_unpause.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../messages/player_choose_perk.hpp"
#include "../cyclic_iterator_impl.hpp"
#include "../perk_type.hpp"
#include <sge/math/clamp.hpp>
#include <sge/math/vector/angle_between.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/resolution.hpp>
#include <sge/log/headers.hpp>
#include <sge/gui/unit.hpp>
#include <sge/structure_cast.hpp>
#include <sge/text.hpp>
#include <sge/optional.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>
#include <algorithm>

sanguis::client::logic::logic(
	send_callback const &send,
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend,
	cursor_pos_callback const &cursor_pos_,
	cursor_show_callback const &cursor_show_)
:
	send(send),
	rend(rend),
	cursor_pos_(cursor_pos_),
	cursor_show_(cursor_show_),
	actions(
		boost::assign::list_of
			(boost::bind(&logic::handle_move_x, this, _1))
			(boost::bind(&logic::handle_move_y, this, _1))
			(boost::bind(&logic::handle_rotation_x, this, _1))
			(boost::bind(&logic::handle_rotation_y, this, _1))
			(boost::bind(&logic::handle_shooting, this, _1))
			(boost::bind(&logic::handle_switch_weapon_forwards, this, _1))
			(boost::bind(&logic::handle_switch_weapon_backwards, this, _1))
			(boost::bind(&logic::handle_pause_unpause, this, _1)).to_container(actions)),
	player_id_(invalid_id),
	direction(0,0),
	cursor_(
		new sanguis::client::cursor(
			il,
			rend)),
	player_center(sge::sprite::point::null()),
	current_weapon(weapon_type::size),
	paused(false),
	rotation_timer(
		sge::time::millisecond(
			100)),
	owned_weapons()
{
	std::fill(
		owned_weapons.begin(),
		owned_weapons.end(),
		false);
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

void sanguis::client::logic::give_weapon(
	messages::give_weapon const &m)
{
	if(m.get<messages::roles::entity_id>() != player_id_)
		return;
	
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
		player_center = sge::structure_cast<
			sge::sprite::point
		>(
			m.get<messages::pos>()
		); // FIXME
}

void sanguis::client::logic::pause(
	bool const p)
{
	paused = p;

	cursor_->visible(paused);
	cursor_show_(!paused);
}

void sanguis::client::logic::remove(
	entity_id const id)
{
	if(id == player_id_)
		player_id_ = invalid_id;
}

void sanguis::client::logic::player_id(
	entity_id const id)
{
	player_id_ = id;
}

sanguis::entity_id sanguis::client::logic::player_id() const
{
	return player_id_;
}

sanguis::client::cursor_ptr 
sanguis::client::logic::cursor()
{
	return cursor_;
}

void sanguis::client::logic::handle_move_x(
	key_scale const s)
{
	direction.x() += s;
	update_direction();
}

void sanguis::client::logic::handle_move_y(
	key_scale const s)
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
				sge::structure_cast<
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
	cursor_->real_pos(
		sge::gui::point(
			sge::math::clamp(
				cursor_->pos().x() + static_cast<sge::gui::unit>(s),
				static_cast<sge::gui::unit>(0),
				static_cast<sge::gui::unit>(
					rend->screen_size().w())),
			cursor_->pos().y()));
	
	update_rotation();
}

void sanguis::client::logic::handle_rotation_y(
	key_scale const s)
{
	cursor_->real_pos(
		sge::gui::point(
			cursor_->pos().x(),
			sge::math::clamp(
				cursor_->pos().y() + static_cast<sge::gui::unit>(s),
				static_cast<sge::gui::unit>(0),
				static_cast<sge::gui::unit>(
					rend->screen_size().h())))
	);

	update_rotation();
}

void sanguis::client::logic::update_rotation()
{
	sge::optional<
		messages::types::space_unit
	> const rotation(
		sge::math::vector::angle_between<messages::types::space_unit>(
			player_center,
			cursor_pos()
		)
	);

	cursor_pos_(
		cursor_pos()
	);

	if(!rotation || !rotation_timer.update_b())
		return;
	
	send(
		messages::create(
			messages::player_rotation(
				player_id_,
				*rotation
			)
		)
	);
}

void sanguis::client::logic::handle_shooting(
	key_scale const s)
{
	if(
		sge::math::compare(
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

	SGE_ASSERT(weapon_index < owned_weapons.size());

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

sge::sprite::point const
sanguis::client::logic::cursor_pos() const
{
	return 
		sge::structure_cast<sge::sprite::point>(
			cursor_->pos());
}
