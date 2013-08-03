#include <sanguis/time_unit.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_weapon::with_weapon(
	sanguis::server::weapons::unique_ptr &&_start_weapon
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_angle(),
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::ifaces::with_team(),
	primary_weapon_(),
	secondary_weapon_(),
	target_(),
	attack_speed_(
		1
	),
	reload_speed_(
		1
	)
{
	if(
		_start_weapon
	)
		this->replace_weapon(
			std::move(
				_start_weapon
			)
		);
}

sanguis::server::entities::with_weapon::~with_weapon()
{
}

void
sanguis::server::entities::with_weapon::on_update()
{
	// TODO: Helper function!
	if(
		primary_weapon_
	)
		primary_weapon_->update(
			*this
		);

	if(
		secondary_weapon_
	)
		secondary_weapon_->update(
			*this
		);
}

sanguis::server::weapons::unique_ptr
sanguis::server::entities::with_weapon::replace_weapon(
	sanguis::server::weapons::unique_ptr &&_ptr
)
{
	primary_weapon_.swap(
		_ptr
	);

	this->on_new_weapon(
		*primary_weapon_
	);

	if(
		this->has_environment()
	)
		this->environment().weapon_changed(
			this->id(),
			primary_weapon_->type()
		);

	if(
		_ptr
	)
		_ptr->stop();

	return
		std::move(
			_ptr
		);
}

void
sanguis::server::entities::with_weapon::target(
	sanguis::server::weapons::target const _target
)
{
	target_ = _target;
}

sanguis::server::weapons::target const
sanguis::server::entities::with_weapon::target() const
{
	FCPPT_ASSERT_PRE(
		target_
	);

	return
		*target_;
}

void
sanguis::server::entities::with_weapon::use_primary(
	bool const _use
)
{
	this->use_weapon(
		primary_weapon_.get(),
		_use
	);
}

void
sanguis::server::entities::with_weapon::use_secondary(
	bool const _use
)
{
	this->use_weapon(
		secondary_weapon_.get(),
		_use
	);
}

/*
void
sanguis::server::entities::with_weapon::start_attacking()
{
	this->environment().attacking_changed(
		this->id(),
		true
	);
}

void
sanguis::server::entities::with_weapon::start_reloading()
{
	this->environment().reloading_changed(
		this->id(),
		true
	);
}

void
sanguis::server::entities::with_weapon::stop_reloading()
{
	this->environment().reloading_changed(
		this->id(),
		false
	);
}*/

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

sanguis::server::weapons::ias const
sanguis::server::entities::with_weapon::ias() const
{
	return
		sanguis::server::weapons::ias(
			attack_speed_.current()
		);
}

sanguis::server::weapons::irs const
sanguis::server::entities::with_weapon::irs() const
{
	return
		sanguis::server::weapons::irs(
			reload_speed_.current()
		);
}

/*
void
sanguis::server::entities::with_weapon::stop_attacking()
{
	this->environment().attacking_changed(
		this->id(),
		false
	);
}*/

void
sanguis::server::entities::with_weapon::use_weapon(
	sanguis::server::weapons::weapon *const _weapon,
	bool const _use
)
{
	if(
		!_weapon
	)
		return;

	if(
		!_use
	)
		_weapon->stop();
	else if(
		target_
	)
		_weapon->attack(
			*this
		);
}

void
sanguis::server::entities::with_weapon::on_new_weapon(
	sanguis::server::weapons::weapon const &
)
{
}
