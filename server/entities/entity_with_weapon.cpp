#include "entity_with_weapon.hpp"
#include "../weapons/factory.hpp"
#include "../weapons/weapon.hpp"
#include "../environment/object.hpp"
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

sanguis::server::pos_type const
target_undefined(
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
	attack_ready_(false),
	aggressive_(false),
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
	),
	reload_speed_change_(
		property(
			property_type::reload_speed
		).register_change_callback(
			boost::bind(
				&entity_with_weapon::reload_speed_change,
				this,
				_1
			)
		)
	)
{
	if(!start_weapon.get())
		return;
	
	add_weapon(
		start_weapon
	);
}

void sanguis::server::entities::entity_with_weapon::update(
	time_type const time
)
{
	entity::update(
		time
	);

	// change to the first weapon if we have any
	if(weapon_ == weapon_type::none && !weapons_.empty())
		change_weapon(
			weapons_.begin()->second->type()
		);


	if(has_weapon())
		active_weapon().update(
			time,
			*this
		);

	bool const in_range_(
		target() != target_undefined
		&& in_range(
			target()
		)
	);

	if (weapon_ == weapon_type::none || !in_range_ || !aggressive_)
	{
		stop_attacking();
		return;
	}
	
	if(!reloading && attack_ready_ && in_range_)
		active_weapon().attack(
			*this,
			target()
		);
}

void sanguis::server::entities::entity_with_weapon::change_weapon(
	weapon_type::type const nweapon)
{
	if (nweapon != weapon_type::none && !weapons_.count(nweapon))
		throw exception(
			SGE_TEXT("tried to change to non-owned weapon")
		);
	
	if(has_weapon())
		active_weapon().stop();
	
	weapon_ = nweapon;

	reloading = false;
	attacking = false;

	if(has_weapon())
	{
		active_weapon().attack_speed(
			property(
				property_type::attack_speed
			).current()
		);

		active_weapon().reload_speed(	
			property(
				property_type::reload_speed
			).current()
		);

		attack_ready_ = true;
	}

	environment()->weapon_changed(
		id(),
		weapon_
	);
}

void sanguis::server::entities::entity_with_weapon::add_weapon(
	weapons::auto_ptr ptr)
{
	weapon_type::type const wt = ptr->type();
	weapons::magazine_type const magazine_size = ptr->magazine_size();

	if(
		wt == weapon_type::pistol
		&& weapons_.count(weapon_type::pistol)
	)
		return add_weapon(
			weapons::create(
				weapon_type::dual_pistol
			)
		);

	{
		weapon_container::iterator const it(
			weapons_.find(
				wt
			)
		);

		// TODO: if we pick up a pistol, the dual pistol gets reset instead.
		// Doesn't make much sense, but what should we do?

		if(it != weapons_.end())
		{
			it->second->repickup();
			return;
		}
	}

	if (!weapons_.insert(wt,ptr).second)
		throw exception(SGE_TEXT("couldn't insert weapon"));

	environment()->got_weapon(
		id(),
		wt
	);
}

void sanguis::server::entities::entity_with_weapon::remove_weapon(
	weapon_type::type const type_)
{
	if(!weapons_.erase(type_))
		throw exception(SGE_TEXT("tried to remove non-owned weapon"));
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

bool
sanguis::server::entities::entity_with_weapon::in_range(
	pos_type const &center
) const
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
	weapon_container::iterator const it(
		weapons_.find(
			weapon_
		)
	);

	if(it == weapons_.end())
		throw exception(
			SGE_TEXT("No weapon active in entity_with_weapon!")
		);
	
	return *it->second;
}

void
sanguis::server::entities::entity_with_weapon::aggressive(
	bool const naggressive
)
{	
	aggressive_ = naggressive;
}

sanguis::server::weapons::weapon const &
sanguis::server::entities::entity_with_weapon::active_weapon() const
{
	return const_cast<entity_with_weapon &>(*this).active_weapon();
}

void
sanguis::server::entities::entity_with_weapon::attack_ready()
{
	attack_ready_ = true;
}

void
sanguis::server::entities::entity_with_weapon::start_attacking()
{
	attack_ready_ = false;

	if(attacking)
		return;
	
	environment()->attacking_changed(
		id(),
		true
	);

	attacking = true;
}

void
sanguis::server::entities::entity_with_weapon::start_reloading()
{
	reloading = true;

	environment()->reloading_changed(
		id(),
		true	
	);
}

void
sanguis::server::entities::entity_with_weapon::stop_reloading()
{
	reloading = false;

	environment()->reloading_changed(
		id(),
		false	
	);
}

void
sanguis::server::entities::entity_with_weapon::stop_attacking()
{
	if(!attacking)
		return;
	
	environment()->reloading_changed(
		id(),
		true
	);

	attacking = false;
}

void
sanguis::server::entities::entity_with_weapon::attack_speed_change(
	property::value_type const v
)
{
	if(has_weapon())
		active_weapon().attack_speed(v);
}

void
sanguis::server::entities::entity_with_weapon::reload_speed_change(
	property::value_type const v
)
{
	if(has_weapon())
		active_weapon().reload_speed(v);
}
