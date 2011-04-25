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
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::with_weapon::with_weapon(
	weapons::unique_ptr _start_weapon
)
:
	base(),
	weapon_(weapon_type::none),
	target_(),
	attacking_(false),
	reloading_(false),
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
	if(
		!_start_weapon.get()
	)
		return;

	this->add_weapon(
		move(
			_start_weapon
		)
	);
}

sanguis::server::entities::with_weapon::~with_weapon()
{
}

void
sanguis::server::entities::with_weapon::on_update(
	sanguis::time_delta const &_time
)
{
	// change to the first weapon if we have any
	if(
		weapon_ == weapon_type::none
		&& !weapons_.empty()
	)
		this->change_weapon(
			weapons_.begin()->second->type()
		);


	if(
		this->has_weapon()
	)
		this->active_weapon().update(
			_time,
			*this
		);

	bool const in_range_(
		target_
		&& this->in_range(
			*target_
		)
	);

	if(
		weapon_ == weapon_type::none
		|| !in_range_
		|| !aggressive_
	)
	{
		this->stop_attacking();

		return;
	}

	if(
		!reloading_
		&& attack_ready_
		&& in_range_
	)
		this->active_weapon().attack(
			*this,
			*target_
		);
}

void
sanguis::server::entities::with_weapon::change_weapon(
	weapon_type::type const _weapon
)
{
	if(
		_weapon != weapon_type::none
		&& !weapons_.count(
			_weapon
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("tried to change to non-owned weapon")
		);

	if(
		this->has_weapon()
	)
		this->active_weapon().stop();

	weapon_ = _weapon;

	reloading_ = false;

	attacking_ = false;

	this->attack_speed_change(
		attack_speed_.current()
	);

	this->reload_speed_change(
		reload_speed_.current()
	);

	if(
		this->has_weapon()
	)
		attack_ready_ = true;

	this->environment().weapon_changed(
		this->id(),
		weapon_
	);
}

void
sanguis::server::entities::with_weapon::add_weapon(
	weapons::unique_ptr _ptr
)
{
	weapon_type::type const wt(
		_ptr->type()
	);

	weapons::magazine_type const magazine_size(
		_ptr->magazine_size().get()
	);

	if(
		wt == weapon_type::pistol
		&& weapons_.count(
			weapon_type::pistol
		)
	)
		return
			this->add_weapon(
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

		if(
			it != weapons_.end()
		)
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
				_ptr
			)
		).second
	)
		throw sanguis::exception(
			FCPPT_TEXT("couldn't insert weapon")
		);

	this->on_new_weapon(
		wt
	);
}

void
sanguis::server::entities::with_weapon::remove_weapon(
	weapon_type::type const _weapon
)
{
	if(
		!weapons_.erase(
			_weapon
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("tried to remove non-owned weapon")
		);
}

void
sanguis::server::entities::with_weapon::target(
	server::vector const &_target
)
{
	target_ = _target;
}

bool
sanguis::server::entities::with_weapon::in_range(
	server::vector const &_pos
) const
{
	return
		this->has_weapon()
		&&
		this->active_weapon().in_range(
			*this,
			_pos
		);
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

	if(
		it == weapons_.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("No weapon active in with_weapon!")
		);

	return *it->second;
}

void
sanguis::server::entities::with_weapon::aggressive(
	bool const _aggressive
)
{
	aggressive_ = _aggressive;
}

sanguis::server::weapons::weapon const &
sanguis::server::entities::with_weapon::active_weapon() const
{
	return
		const_cast<
			with_weapon &
		>(
			*this
		).active_weapon();
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

	if(
		attacking_
	)
		return;

	this->environment().attacking_changed(
		this->id(),
		true
	);

	attacking_ = true;
}

void
sanguis::server::entities::with_weapon::start_reloading()
{
	reloading_ = true;

	this->environment().reloading_changed(
		this->id(),
		true
	);
}

void
sanguis::server::entities::with_weapon::stop_reloading()
{
	reloading_ = false;

	this->environment().reloading_changed(
		this->id(),
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
	if(
		!attacking_
	)
		return;

	this->environment().attacking_changed(
		this->id(),
		false
	);

	attacking_ = false;
}

void
sanguis::server::entities::with_weapon::attack_speed_change(
	property::value const _value
)
{
	if(
		this->has_weapon()
	)
		this->active_weapon().attack_speed(
			property::to_float<
				space_unit
			>(
				_value
			)
		);
}

void
sanguis::server::entities::with_weapon::reload_speed_change(
	property::value const _value
)
{
	if(
		this->has_weapon()
	)
		this->active_weapon().reload_speed(
			property::to_float<
				space_unit
			>(
				_value
			)
		);
}

void
sanguis::server::entities::with_weapon::on_new_weapon(
	weapon_type::type const
)
{
}
