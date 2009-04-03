#include "entity_with_weapon.hpp"
#include "../message_convert/start_reloading.hpp"
#include "../message_convert/stop_reloading.hpp"
#include "../message_convert/start_attacking.hpp"
#include "../message_convert/stop_attacking.hpp"
#include "../weapons/factory.hpp"
#include "../weapons/weapon.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/create.hpp"
#include "../../truncation_check_cast.hpp"
#include "../../exception.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <limits>

namespace
{

sanguis::server::pos_type const target_undefined(
	std::numeric_limits<sanguis::server::space_unit>::max(),
	std::numeric_limits<sanguis::server::space_unit>::max());

}

sanguis::server::entities::entity_with_weapon::entity_with_weapon(
	base_parameters const &param,
	weapons::auto_ptr start_weapon)
:
	entity(param),
	weapon_(weapon_type::none),
	target_(target_undefined),
	attacking(false),
	reloading(false),
	attack_speed_change_(
		property(
			property_type::attack_speed
		).register_change_callback(
			boost::bind(
				&entity_with_weapon::attack_speed_change,
				this,
				_1
			)
		)
	)
{
	if(!start_weapon.get())
		return;
	
	add_weapon(
		start_weapon);
}

void sanguis::server::entities::entity_with_weapon::update(
	time_type const time,
	container &entities)
{
	entity::update(
		time,
		entities);

	// change to the first weapon if we have any
	if(weapon_ == weapon_type::none && !weapons_.empty())
		change_weapon(
			weapons_.begin()->second->type());


	if(has_weapon())
	{
		active_weapon().update(
			time,
			*this);

		if(active_weapon().reloading() && !reloading)
		{
			send(message_convert::start_reloading(*this));
			reloading = true;
		}
		else if(reloading && !active_weapon().reloading())
		{
			send(message_convert::stop_reloading(*this));
			reloading = false;
		}
	}

	// entity lost its target and/or weapon or aggression or didn't have any of these
	if (weapon_ == weapon_type::none || target() == target_undefined || !aggressive())
	{
		// previously attacking
		if (attacking)
		{
			send(message_convert::stop_attacking(*this));
			attacking = false;
		}

		return;
	}

	// all requirements for an attack are met?
	// -has a weapon
	// -has a target
	// -is aggressive
	if (!has_weapon() || target() == target_undefined || !aggressive())
		return;

	weapons::weapon &wep(active_weapon());
	if (wep.attack(*this, target()) && !attacking)
	{
		send(message_convert::start_attacking(*this));
		attacking = true;
	}
	else if (attacking && wep.ready())
	{
		send(message_convert::stop_attacking(*this));
		attacking = false;
	}
}

void sanguis::server::entities::entity_with_weapon::change_weapon(
	weapon_type::type const nweapon)
{
	if (nweapon != weapon_type::none && !weapons_.count(nweapon))
		throw exception(
			SGE_TEXT("tried to change to non-owned weapon"));
	
	weapon_ = nweapon;

	if(has_weapon())
		active_weapon().attack_speed(
			property(
				property_type::attack_speed
			).current()
		);

	send(
		messages::create(
			messages::change_weapon(
				id(),
				weapon_
			)
		)
	);
}

void sanguis::server::entities::entity_with_weapon::add_weapon(
	weapons::auto_ptr ptr)
{
	weapon_type::type const wt = ptr->type();
	unsigned const magazine_size = ptr->magazine_size();

	if(wt == weapon_type::pistol && weapons_.count(weapon_type::pistol))
		return add_weapon(
			weapons::create(
				weapon_type::dual_pistol,
				environment()
			)
		);

	if (weapons_.count(wt))
		return;

	if (!weapons_.insert(wt,ptr).second)
		throw exception(SGE_TEXT("couldn't insert weapon"));

	send(
		messages::create(
			messages::give_weapon(
				id(),
				wt
			)
		)
	);
}

void sanguis::server::entities::entity_with_weapon::remove_weapon(
	weapon_type::type const type_)
{
	if (weapons_.find(type_) == weapons_.end())
		throw exception(SGE_TEXT("tried to remove non-owned weapon"));
	
	weapons_.erase(type_);
}

void sanguis::server::entities::entity_with_weapon::target(
	pos_type const &ntarget)
{
	target_ = ntarget;
}

sanguis::server::pos_type const &
sanguis::server::entities::entity_with_weapon::target() const
{
	return target_;
}

bool sanguis::server::entities::entity_with_weapon::in_range(
	pos_type const &center) const
{
	return has_weapon() && active_weapon().in_range(*this, center);
}

bool sanguis::server::entities::entity_with_weapon::has_weapon() const
{
	return weapon_ != weapon_type::none;	
}

sanguis::server::weapons::weapon &
sanguis::server::entities::entity_with_weapon::active_weapon()
{
	weapon_container::iterator const it(weapons_.find(weapon_));
	if(it == weapons_.end())
		throw exception(
			SGE_TEXT("No weapon active in entity_with_weapon!")
		);
	return *it->second;
}

sanguis::server::weapons::weapon const &
sanguis::server::entities::entity_with_weapon::active_weapon() const
{
	return const_cast<entity_with_weapon &>(*this).active_weapon();
}

void
sanguis::server::entities::entity_with_weapon::attack_speed_change(
	property::value_type const v)
{
	if(has_weapon())
		active_weapon().attack_speed(v);
}
