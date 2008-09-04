#include "logic.hpp"
#include <boost/bind.hpp>
#include <algorithm>
#include <cassert>

sanguis::client::logic::logic(
	send_callback const &send)
:
	send(send),
	actions(
		boost::bind(&logic::handle_move_x, this, _1),
		boost::bind(&logic::handle_move_y, this, _1),
		boost::bind(&logic::handle_rotation_x, this, _1),
		boost::bind(&logic::handle_rotation_y, this, _1),
		boost::bind(&logic::handle_shooting, this, _1),
		boost::bind(&logic::handle_switch_weapon_fowards, this, _1),
		boost::bind(&logic::handle_switch_weapon_backwards, this, _1),
		boost::bind(&logic::handle_pause_unpause, this, _1)),
	player_id(0),
	direction(0,0),
	cursor_pos(0,0),
	current_weapon(weapons::size),
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
		return; // FIXME
	
	owned_weapons[m.weapon()] = true;

	// we don't own any weapon so take this one
	if(current_weapon == weapon_type::size)
		change_weapon(
			m.id(),
			static_cast<weapon_type::type>(
				m.weapon()));
}

void sanguis::client::running_state::handle_move_x(
	key_scale const s)
{
	direction.x() += s;
	update_direction();
}

void sanguis::client::running_state::handle_move_y(
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
				player.id(),
				sge::math::structure_cast<messages::space_unit>(
					direction))));
}

void sanguis::client::logic::handle_rotation_x(
	key_scale const s)
{
	cursor_pos.x() += static_cast<sge::sprite::unit>(s);
	cursor_pos.x() = sge::math::clamp(
		cursor_pos.x(),
		0,
		screen_sz.w());
	
	update_rotation();
}

void sanguis::client::logic::handle_rotation_y(
	key_scale const s)
{
	cursor_pos.y() += static_cast<sge::sprite::unit>(m.scale());
	cursor_pos.y() = sge::math::clamp(
		cursor_pos.y(),
		0,
		screen_sz.h());

	update_rotation();
}

void sanguis::client::logic::update_rotation()
{
	boost::optional<sge::space_unit> const rotation(
		sge::math::angle_to<sge::space_unit>(
			player_center,
			cursor_pos));
	if(!rotation)
		return;

	send(
		messages::auto_ptr(
			new messages::player_rotation(
				player_id,
				messages::mu(
					*rotation))));

	/*drawer.process_message(
		messages::move(
			cursor_id,
			screen_to_virtual(rend->screen_size(),cursor_pos-sge::sprite::point(32,32))));*/

}

void sanguis::client::running_state::handle_shooting(
	key_scale const s)
{
	send(
		messages::auto_ptr(
			sge::math::compare(
				static_cast<key_scale>(0),
				s)
			? static_cast<messages::base*>(
				new messages::player_stop_shooting(
					p.id()))
			: static_cast<messages::base*>(
				new messages::player_start_shooting(
					p.id()))));
}

void sanguis::client::running_state::handle_switch_weapon_forwards(
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

	switch(m.type()) {
	case player_action::switch_weapon_forwards:
		while(!*++it) ;
		break;
	case player_action::switch_weapon_backwards:
		while(!*--it) ;
		break;
	default:
		return;
	}

	change_weapon(
		player_id,
		static_cast<weapon_type::type>(
			std::distance(
				static_cast<owned_weapons_array const &>(
					owned_weapons).begin(),
				it.get())));
}

void sanguis::client::logic::handle_switch_weapon_backwards(
	key_scale)
{}

void sanguis::client::running_state::handle_pause_unpause(
	key_scale)
{
	context<machine>().send(
		messages::auto_ptr(
			paused
			? static_cast<messages::base*>(
				new messages::player_unpause(
					player_id))
			: static_cast<messages::base*>(
				new messages::player_pause(
					player_id))));
}

void sanguis::client::running_state::change_weapon(
	weapon_type::type const w)
{
	current_weapon = w;

	context<machine>().send(
		messages::auto_ptr(
			new messages::player_change_weapon(
				player_id,
				current_weapon)));
}
