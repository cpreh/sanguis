#include "with_weapon.hpp"
#include "property/to_float.hpp"
#include "../weapons/create.hpp"
#include "../weapons/weapon.hpp"
#include "../environment/object.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/create.hpp"
#include "../../exception.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <limits>

namespace
{

sanguis::server::pos_type const
target_undefined(
	std::numeric_limits<sanguis::server::space_unit>::max(),
	std::numeric_limits<sanguis::server::space_unit>::max());

}

sanguis::server::entities::with_weapon::with_weapon(
	weapons::unique_ptr _start_weapon
)
:
	base(),
	weapon_(weapon_type::none),
	target_(target_undefined),
	attacking(false),
	reloading(false),
	attack_ready_(false),
	aggressive_(false),
	attack_speed_(
		1
	),
	reload_speed_(
		1
	),
	attack_speed_change_(
		attack_speed_.register_change_callback(
			std::tr1::bind(
				&with_weapon::attack_speed_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	reload_speed_change_(
		reload_speed_.register_change_callback(
			std::tr1::bind(
				&with_weapon::reload_speed_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	if(!_start_weapon.get())
		return;

	add_weapon(
		move(
			_start_weapon
		)
	);
}

void
sanguis::server::entities::with_weapon::on_update(
	time_type const time
)
{
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
		target_ != target_undefined
		&& in_range(
			target_
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
			target_
		);
}

void
sanguis::server::entities::with_weapon::change_weapon(
	weapon_type::type const nweapon
)
{
	if (nweapon != weapon_type::none && !weapons_.count(nweapon))
		throw exception(
			FCPPT_TEXT("tried to change to non-owned weapon")
		);

	if(has_weapon())
		active_weapon().stop();

	weapon_ = nweapon;

	reloading = false;
	attacking = false;

	attack_speed_change(
		attack_speed_.current()
	);

	reload_speed_change(
		reload_speed_.current()
	);

	if(has_weapon())
		attack_ready_ = true;

	environment()->weapon_changed(
		id(),
		weapon_
	);
}

void
sanguis::server::entities::with_weapon::add_weapon(
	weapons::unique_ptr ptr
)
{
	weapon_type::type const wt(
		ptr->type()
	);

	weapons::magazine_type const magazine_size(
		ptr->magazine_size()
	);

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

	if(
		!fcppt::container::ptr::insert_unique_ptr_map(
			weapons_,
			wt,
			move(
				ptr
			)
		).second
	)
		throw exception(
			FCPPT_TEXT("couldn't insert weapon")
		);

	on_new_weapon(
		wt
	);
}

void
sanguis::server::entities::with_weapon::remove_weapon(
	weapon_type::type const type_
)
{
	if(!weapons_.erase(type_))
		throw exception(FCPPT_TEXT("tried to remove non-owned weapon"));
}

void
sanguis::server::entities::with_weapon::target(
	pos_type const &ntarget
)
{
	target_ = ntarget;
}

bool
sanguis::server::entities::with_weapon::in_range(
	pos_type const &center
) const
{
	return has_weapon() && active_weapon().in_range(*this, center);
}

bool
sanguis::server::entities::with_weapon::has_weapon() const
{
	return weapon_ != weapon_type::none;
}

sanguis::server::weapons::weapon &
sanguis::server::entities::with_weapon::active_weapon()
{
	weapon_container::iterator const it(
		weapons_.find(
			weapon_
		)
	);

	if(it == weapons_.end())
		throw exception(
			FCPPT_TEXT("No weapon active in with_weapon!")
		);

	return *it->second;
}

void
sanguis::server::entities::with_weapon::aggressive(
	bool const naggressive
)
{
	aggressive_ = naggressive;
}

sanguis::server::weapons::weapon const &
sanguis::server::entities::with_weapon::active_weapon() const
{
	return const_cast<with_weapon &>(*this).active_weapon();
}

void
sanguis::server::entities::with_weapon::attack_ready()
{
	attack_ready_ = true;
}

void
sanguis::server::entities::with_weapon::start_attacking()
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
sanguis::server::entities::with_weapon::start_reloading()
{
	reloading = true;

	environment()->reloading_changed(
		id(),
		true
	);
}

void
sanguis::server::entities::with_weapon::stop_reloading()
{
	reloading = false;

	environment()->reloading_changed(
		id(),
		false
	);
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_weapon::attack_speed()
{
	return attack_speed_;
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_weapon::reload_speed()
{
	return reload_speed_;
}

void
sanguis::server::entities::with_weapon::stop_attacking()
{
	if(!attacking)
		return;

	environment()->attacking_changed(
		id(),
		false
	);

	attacking = false;
}

void
sanguis::server::entities::with_weapon::attack_speed_change(
	property::value const value_
)
{
	if(has_weapon())
		active_weapon().attack_speed(
			property::to_float<
				space_unit
			>(
				value_
			)
		);
}

void
sanguis::server::entities::with_weapon::reload_speed_change(
	property::value const value_
)
{
	if(has_weapon())
		active_weapon().reload_speed(
			property::to_float<
				space_unit
			>(
				value_
			)
		);
}

void
sanguis::server::entities::with_weapon::on_new_weapon(
	weapon_type::type const
)
{
}
