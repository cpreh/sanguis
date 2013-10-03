#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/time_unit.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/const_optional_ref.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/unique_ptr_to_optional.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/variant/get.hpp>
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
		this->pickup_weapon(
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
	this->update_weapon(
		this->primary_weapon_ref()
	);

	if(
		secondary_weapon_
		&&
		!secondary_weapon_->usable()
	)
	{
		this->drop_weapon(
			sanguis::is_primary_weapon(
				false
			)
		);
	}

	this->update_weapon(
		this->secondary_weapon_ref()
	);
}

sanguis::optional_primary_weapon_type const
sanguis::server::entities::with_weapon::primary_weapon_type() const
{
	return
		primary_weapon_
		?
			sanguis::optional_primary_weapon_type(
				fcppt::variant::get<
					sanguis::primary_weapon_type
				>(
					primary_weapon_->type()
				)
			)
		:
			sanguis::optional_primary_weapon_type()
		;
}

sanguis::string_vector const
sanguis::server::entities::with_weapon::primary_weapon_text() const
{
	return
		primary_weapon_
		?
			primary_weapon_->description().text()
		:
			sanguis::string_vector()
		;
}

void
sanguis::server::entities::with_weapon::pickup_weapon(
	sanguis::server::weapons::unique_ptr &&_ptr
)
{
	if(
		!_ptr
	)
		return;

	sanguis::is_primary_weapon const is_primary(
		sanguis::weapon_type_to_is_primary(
			_ptr->type()
		)
	);

	sanguis::server::weapons::unique_ptr &dest(
		this->is_primary_to_weapon_unique_ptr(
			is_primary
		)
	);

	dest.swap(
		_ptr
	);

	this->on_new_weapon(
		*dest
	);

	this->weapon_changed(
		is_primary
	);

	if(
		_ptr
	)
		_ptr->stop();
}

sanguis::server::weapons::unique_ptr
sanguis::server::entities::with_weapon::drop_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	sanguis::server::weapons::unique_ptr result(
		std::move(
			this->is_primary_to_weapon_unique_ptr(
				_is_primary
			)
		)
	);

	this->on_drop_weapon(
		_is_primary
	);

	this->weapon_changed(
		_is_primary
	);

	return
		std::move(
			result
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

bool
sanguis::server::entities::with_weapon::in_range(
	sanguis::is_primary_weapon const _is_primary
) const
{
	sanguis::server::entities::with_weapon::optional_weapon_ref const weapon(
		this->is_primary_to_optional_weapon(
			_is_primary
		)
	);

	return
		target_
		&&
		weapon->in_range(
			*this,
			*target_
		);
}

void
sanguis::server::entities::with_weapon::use_weapon(
	bool const _use,
	sanguis::is_primary_weapon const _is_primary
)
{
	sanguis::server::entities::with_weapon::optional_weapon_ref const weapon(
		this->is_primary_to_optional_weapon(
			_is_primary
		)
	);

	if(
		!weapon
	)
		return;

	if(
		!_use
	)
		weapon->stop();
	else if(
		target_
	)
		weapon->attack(
			*this
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

sanguis::server::weapons::const_optional_ref const
sanguis::server::entities::with_weapon::primary_weapon() const
{
	return
		sanguis::server::weapons::const_optional_ref(
			fcppt::unique_ptr_to_optional(
				primary_weapon_
			)
		);
}

sanguis::server::weapons::const_optional_ref const
sanguis::server::entities::with_weapon::secondary_weapon() const
{
	return
		sanguis::server::weapons::const_optional_ref(
			fcppt::unique_ptr_to_optional(
				secondary_weapon_
			)
		);
}

void
sanguis::server::entities::with_weapon::attacking(
	bool const _value,
	sanguis::weapon_type const _type
)
{
	if(
		sanguis::weapon_type_to_is_primary(
			_type
		).get()
	)
		this->environment().attacking_changed(
			this->id(),
			_value
		);
}

void
sanguis::server::entities::with_weapon::reloading(
	bool const _value,
	sanguis::weapon_type const _type
)
{
	if(
		sanguis::weapon_type_to_is_primary(
			_type
		).get()
	)
		this->environment().reloading_changed(
			this->id(),
			_value
		);
}

sanguis::server::entities::with_weapon::optional_weapon_ref const
sanguis::server::entities::with_weapon::primary_weapon_ref() const
{
	return
		fcppt::unique_ptr_to_optional(
			primary_weapon_
		);
}

sanguis::server::entities::with_weapon::optional_weapon_ref const
sanguis::server::entities::with_weapon::secondary_weapon_ref() const
{
	return
		fcppt::unique_ptr_to_optional(
			secondary_weapon_
		);
}

sanguis::server::entities::with_weapon::optional_weapon_ref const
sanguis::server::entities::with_weapon::is_primary_to_optional_weapon(
	sanguis::is_primary_weapon const _is_primary
) const
{
	return
		_is_primary.get()
		?
			this->primary_weapon_ref()
		:
			this->secondary_weapon_ref()
		;
}

sanguis::server::weapons::unique_ptr &
sanguis::server::entities::with_weapon::is_primary_to_weapon_unique_ptr(
	sanguis::is_primary_weapon const _is_primary
)
{
	return
		_is_primary.get()
		?
			primary_weapon_
		:
			secondary_weapon_
		;
}

void
sanguis::server::entities::with_weapon::update_weapon(
	sanguis::server::entities::with_weapon::optional_weapon_ref const &_weapon
)
{
	if(
		_weapon
	)
		_weapon->update(
			*this
		);
}

void
sanguis::server::entities::with_weapon::weapon_changed(
	sanguis::is_primary_weapon const _is_primary
)
{
	if(
		this->has_environment()
		&&
		_is_primary.get()
	)
		this->environment().weapon_changed(
			this->id(),
			this->primary_weapon_type()
		);
}

void
sanguis::server::entities::with_weapon::on_new_weapon(
	sanguis::server::weapons::weapon const &
)
{
}

void
sanguis::server::entities::with_weapon::on_drop_weapon(
	sanguis::is_primary_weapon
)
{
}
