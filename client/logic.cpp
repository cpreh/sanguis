#include "logic.hpp"
#include "../messages/give_weapon.hpp"
#include "../messages/move.hpp"
#include "../messages/player_direction.hpp"
#include "../messages/player_rotation.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/player_pause.hpp"
#include "../messages/player_unpause.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../cyclic_iterator_impl.hpp"
#include <sge/math/clamp.hpp>
#include <sge/math/angle.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cassert>

sanguis::client::logic::logic(
	send_callback const &send,
	sge::renderer::device_ptr const rend)
:
	send(send),
	rend(rend),
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
	player_id(0),
	direction(0,0),
	cursor_pos_(0,0),
	player_center(0,0),
	current_weapon(weapon_type::size),
	paused(false)
{
	std::fill(owned_weapons.begin(), owned_weapons.end(), false); // TODO: boost::array doesn't initialize by default?
}

void sanguis::client::logic::handle_player_action(
	player_action const &action)
{
	actions.at(
		action.type())(
			action.scale());
}

void sanguis::client::logic::give_weapon(
	messages::give_weapon const &m)
{
	if(m.id() != player_id)
		return;
	
	owned_weapons.at(m.weapon()) = true;

	// we don't own any weapon so take this one
	if(current_weapon == weapon_type::size)
		change_weapon(
			static_cast<weapon_type::type>(
				m.weapon()));
}

void sanguis::client::logic::move(
	messages::move const &m)
{
	if(m.id() == player_id)
		player_center = sge::math::structure_cast<
			sge::sprite::unit>(
				m.pos()); // FIXME
}

void sanguis::client::logic::pause(
	bool const p)
{
	paused = p;
}

sge::sprite::point const
sanguis::client::logic::cursor_pos() const
{
	return cursor_pos_;
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
		messages::auto_ptr(
			new messages::player_direction(
				player_id,
				sge::math::structure_cast<messages::space_unit>(
					direction))));
}

void sanguis::client::logic::handle_rotation_x(
	key_scale const s)
{
	cursor_pos_.x() += static_cast<sge::sprite::unit>(s);
	cursor_pos_.x() = sge::math::clamp(
		cursor_pos_.x(),
		0,
		static_cast<sge::sprite::unit>(
			rend->screen_width()));
	
	update_rotation();
}

void sanguis::client::logic::handle_rotation_y(
	key_scale const s)
{
	cursor_pos_.y() += static_cast<sge::sprite::unit>(s);
	cursor_pos_.y() = sge::math::clamp(
		cursor_pos_.y(),
		0,
		static_cast<sge::sprite::unit>(
			rend->screen_height()));

	update_rotation();
}

void sanguis::client::logic::update_rotation()
{
	boost::optional<sge::space_unit> const rotation(
		sge::math::angle_to<sge::space_unit>(
			player_center,
			cursor_pos_));
	if(!rotation)
		return;

	send(
		messages::auto_ptr(
			new messages::player_rotation(
				player_id,
				messages::mu(
					*rotation))));
}

void sanguis::client::logic::handle_shooting(
	key_scale const s)
{
	send(
		messages::auto_ptr(
			sge::math::compare(
				static_cast<key_scale>(0),
				s)
			? static_cast<messages::base*>(
				new messages::player_stop_shooting(
					player_id))
			: static_cast<messages::base*>(
				new messages::player_start_shooting(
					player_id))));
}

void sanguis::client::logic::handle_switch_weapon_forwards(
	key_scale)
{
	// we don't own any weapon
	if(current_weapon == weapon_type::size)
		return;

	owned_weapons_array::size_type const weapon_index(
		static_cast<owned_weapons_array::size_type>(
			current_weapon));

	assert(weapon_index < owned_weapons.size());

	cyclic_iterator<owned_weapons_array::const_iterator> it(
		owned_weapons.begin()
		+ static_cast<owned_weapons_array::size_type>(current_weapon),
		owned_weapons.begin(),
		owned_weapons.end());

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
					owned_weapons).begin(),
				it.get())));
}

void sanguis::client::logic::handle_switch_weapon_backwards(
	key_scale)
{}

void sanguis::client::logic::handle_pause_unpause(
	key_scale)
{
	send(
		messages::auto_ptr(
			paused
			? static_cast<messages::base*>(
				new messages::player_unpause(
					player_id))
			: static_cast<messages::base*>(
				new messages::player_pause(
					player_id))));
}

void sanguis::client::logic::change_weapon(
	weapon_type::type const w)
{
	current_weapon = w;

	send(
		messages::auto_ptr(
			new messages::player_change_weapon(
				player_id,
				current_weapon)));
}
