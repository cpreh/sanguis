#include "logic.hpp"
#include "invalid_id.hpp"
#include "../messages/give_weapon.hpp"
#include "../messages/move.hpp"
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
#include <sge/math/angle.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/console/console.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/structure_cast.hpp>
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
	player_id_(invalid_id),
	direction(0,0),
	cursor_pos_(0,0),
	player_center(0,0),
	current_weapon(weapon_type::size),
	paused(false),
	rotation_timer(
		sge::time::millisecond(
			100))
{
	// FIXME: this needs some sort of RAII connection class
	sge::con::add(
		SGE_TEXT("giveperk"),
		boost::bind(
			&logic::give_perk,
			this,
			_1));

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
		action.type())(
			action.scale());
}

void sanguis::client::logic::give_weapon(
	messages::give_weapon const &m)
{
	if(m.id() != player_id_)
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
	if(m.id() == player_id_)
		player_center = sge::structure_cast<
			sge::sprite::point
		>(
			m.pos()); // FIXME
}

void sanguis::client::logic::pause(
	bool const p)
{
	paused = p;
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
				player_id_,
				sge::structure_cast<
					messages::vector2
				>(
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
			rend->screen_size().w()));
	
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
			rend->screen_size().h()));

	update_rotation();
}

void sanguis::client::logic::update_rotation()
{
	boost::optional<messages::space_unit> const rotation(
		sge::math::angle_to<messages::space_unit>(
			player_center,
			cursor_pos_));

	if(!rotation || !rotation_timer.update_b())
		return;
	
	send(
		messages::auto_ptr(
			new messages::player_rotation(
				player_id_,
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
					player_id_))
			: static_cast<messages::base*>(
				new messages::player_start_shooting(
					player_id_))));
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
					player_id_))
			: static_cast<messages::base*>(
				new messages::player_pause(
					player_id_))));
}

void sanguis::client::logic::change_weapon(
	weapon_type::type const w)
{
	current_weapon = w;

	send(
		messages::auto_ptr(
			new messages::player_change_weapon(
				player_id_,
				current_weapon)));
}

// TODO: this is only here temporary
namespace
{

sanguis::perk_type::type
to_perk_type(
	sge::string const &s)
{
	if(s == SGE_TEXT("ims"))
		return sanguis::perk_type::ims;
	return sanguis::perk_type::size;
}

}

void sanguis::client::logic::give_perk(
	sge::con::arg_list const &args)
{
	if(args.size() != 2)
		return;
	
	perk_type::type const pt(
		to_perk_type(
			args[1]));
	if(pt != perk_type::size)
		send(
			messages::auto_ptr(
				new messages::player_choose_perk(
					player_id_,
					pt)));

}
