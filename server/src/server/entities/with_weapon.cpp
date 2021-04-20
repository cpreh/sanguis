#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/time_unit.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_with_weapon_ref.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/const_optional_ref.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/move_clear.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_weapon::with_weapon(
	sanguis::server::weapons::optional_unique_ptr &&_opt_start_weapon,
	sanguis::server::weapons::ias const _ias,
	sanguis::server::weapons::irs const _irs
)
:
	primary_weapon_(),
	secondary_weapon_(),
	target_(),
	weapon_status_(
		sanguis::weapon_status::nothing
	),
	attack_speed_(
		_ias.get()
	),
	reload_speed_(
		_irs.get()
	),
	extra_damages_{
		fcppt::enum_::array_init<
			extra_damage_array
		>(
			[](auto)
			{
				return
					sanguis::server::entities::property::always_max(
						0.F
					);
			}
		)
	}
{
	fcppt::optional::maybe_void(
		std::move(
			_opt_start_weapon
		),
		[
			this
		](
			sanguis::server::weapons::unique_ptr &&_start_weapon
		)
		{
			this->pickup_weapon(
				std::move(
					_start_weapon
				)
			);
		}
	);
}

sanguis::server::entities::with_weapon::~with_weapon()
= default;

void
sanguis::server::entities::with_weapon::update()
{
	with_weapon::update_weapon(
		this->primary_weapon_ref()
	);

	with_weapon::update_weapon(
		this->secondary_weapon_ref()
	);
}

void
sanguis::server::entities::with_weapon::tick(
	sanguis::duration const &_duration
)
{
	sanguis::server::entities::base::tick(
		_duration
	);

	with_weapon::tick_weapon(
		_duration,
		this->primary_weapon_ref()
	);

	with_weapon::tick_weapon(
		_duration,
		this->secondary_weapon_ref()
	);
}

sanguis::optional_primary_weapon_type
sanguis::server::entities::with_weapon::primary_weapon_type() const
{
	return
		fcppt::optional::map(
			this->primary_weapon(),
			[](
				fcppt::reference<
					sanguis::server::weapons::weapon const
				> const _primary_weapon
			)
			{
				return
					FCPPT_ASSERT_OPTIONAL_ERROR(
						fcppt::variant::to_optional<
							sanguis::primary_weapon_type
						>(
							_primary_weapon.get().type()
						)
					);
			}
		);
}

void
sanguis::server::entities::with_weapon::pickup_weapon(
	sanguis::server::weapons::unique_ptr &&_ptr
)
{
	sanguis::is_primary_weapon const is_primary(
		sanguis::weapon_type_to_is_primary(
			_ptr->type()
		)
	);

	FCPPT_ASSERT_ERROR(
		!this->get_weapon(
			is_primary
		).has_value()
	);

	sanguis::server::weapons::weapon &ref(
		this->set_weapon(
			is_primary,
			std::move(
				_ptr
			)
		)
	);

	ref.owner(
		sanguis::server::entities::optional_with_weapon_ref(
			fcppt::make_ref(
				*this
			)
		)
	);

	this->on_new_weapon(
		ref
	);

	this->weapon_changed(
		is_primary
	);
}

sanguis::server::weapons::optional_unique_ptr
sanguis::server::entities::with_weapon::drop_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	return
		fcppt::optional::map(
			this->move_weapon(
				_is_primary
			),
			[
				this,
				_is_primary
			](
				sanguis::server::weapons::unique_ptr &&_result
			)
			{
				this->on_drop_weapon(
					_is_primary
				);

				this->weapon_changed(
					_is_primary
				);

				_result->owner(
					sanguis::server::entities::optional_with_weapon_ref()
				);

				return
					std::move(
						_result
					);
			}
		);
}

void
sanguis::server::entities::with_weapon::target(
	sanguis::server::weapons::optional_target const _target
)
{
	target_ =
		_target;
}

sanguis::server::weapons::optional_target
sanguis::server::entities::with_weapon::target() const
{
	return
		target_;
}

bool
sanguis::server::entities::with_weapon::in_range(
	sanguis::is_primary_weapon const _is_primary
) const
{
	return
		fcppt::optional::maybe(
			this->get_weapon(
				_is_primary
			),
			fcppt::const_(
				false
			),
			[](
				fcppt::reference<
					sanguis::server::weapons::weapon
				> const _weapon
			)
			{
				return
					_weapon.get().owner_target_in_range();
			}
		);
}

void
sanguis::server::entities::with_weapon::use_weapon(
	bool const _use,
	sanguis::is_primary_weapon const _is_primary
)
{
	fcppt::optional::maybe_void(
		this->get_weapon(
			_is_primary
		),
		[
			_use,
			this
		](
			fcppt::reference<
				sanguis::server::weapons::weapon
			> const _weapon
		)
		{
			if(
				!_use
			)
			{
				_weapon.get().stop();
			}
			else if(
				target_.has_value()
			)
			{
				_weapon.get().attack();
			}
		}
	);
}

void
sanguis::server::entities::with_weapon::reload(
	sanguis::is_primary_weapon const _is_primary
)
{
	fcppt::optional::maybe_void(
		this->get_weapon(
			_is_primary
		),
		[](
			fcppt::reference<
				sanguis::server::weapons::weapon
			> const _weapon
		)
		{
			_weapon.get().reload();
		}
	);
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_weapon::attack_speed()
{
	return
		attack_speed_;
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_weapon::reload_speed()
{
	return
		reload_speed_;
}

sanguis::server::entities::property::always_max &
sanguis::server::entities::with_weapon::extra_damage(
	sanguis::server::damage::type const _damage_type
)
{
	return
		extra_damages_[
			_damage_type
		];
}

sanguis::server::damage::unit
sanguis::server::entities::with_weapon::extra_damage_value(
	sanguis::server::damage::type const _damage_type
) const
{
	return
		sanguis::server::damage::unit(
			extra_damages_[
				_damage_type
			].current()
		);
}

sanguis::server::weapons::ias
sanguis::server::entities::with_weapon::ias() const
{
	return
		sanguis::server::weapons::ias(
			attack_speed_.current()
		);
}

sanguis::server::weapons::irs
sanguis::server::entities::with_weapon::irs() const
{
	return
		sanguis::server::weapons::irs(
			reload_speed_.current()
		);
}

sanguis::server::weapons::const_optional_ref
sanguis::server::entities::with_weapon::primary_weapon() const
{
	return
		fcppt::optional::map(
			fcppt::optional::deref(
				primary_weapon_
			),
			[](
				fcppt::reference<
					sanguis::server::weapons::weapon
				> const _weapon
			)
			{
				return
					fcppt::make_cref(
						_weapon.get()
					);
			}
		);
}

sanguis::server::weapons::const_optional_ref
sanguis::server::entities::with_weapon::secondary_weapon() const
{
	return
		fcppt::optional::map(
			fcppt::optional::deref(
				secondary_weapon_
			),
			[](
				fcppt::reference<
					sanguis::server::weapons::weapon
				> const _weapon
			)
			{
				return
					fcppt::make_cref(
						_weapon.get()
					);
			}
		);
}

void
sanguis::server::entities::with_weapon::weapon_status(
	sanguis::weapon_status const _weapon_status,
	sanguis::server::weapons::weapon const &_weapon
)
{
	if(
		!sanguis::weapon_type_to_is_primary(
			_weapon.type()
		).get()
	)
	{
		return;
	}

	if(
		weapon_status_
		==
		_weapon_status
	)
	{
		return;
	}

	weapon_status_ =
		_weapon_status;

	FCPPT_ASSERT_OPTIONAL_ERROR(
		this->environment()
	).get().weapon_status_changed(
		this->id(),
		_weapon_status
	);
}

void
sanguis::server::entities::with_weapon::reload_time(
	sanguis::duration const _reload_time,
	sanguis::server::weapons::weapon const &_weapon
)
{
	this->on_reload_time(
		sanguis::weapon_type_to_is_primary(
			_weapon.type()
		),
		_reload_time
	);
}

void
sanguis::server::entities::with_weapon::magazine_remaining(
	sanguis::magazine_remaining const _magazine_remaining,
	sanguis::server::weapons::weapon const &_weapon
)
{
	this->on_magazine_remaining(
		sanguis::weapon_type_to_is_primary(
			_weapon.type()
		),
		_magazine_remaining
	);
}

sanguis::weapon_status
sanguis::server::entities::with_weapon::weapon_status() const
{
	return
		weapon_status_;
}

sanguis::server::entities::with_weapon::optional_weapon_ref
sanguis::server::entities::with_weapon::primary_weapon_ref() const
{
	return
		fcppt::optional::deref(
			primary_weapon_
		);
}

sanguis::server::entities::with_weapon::optional_weapon_ref
sanguis::server::entities::with_weapon::secondary_weapon_ref() const
{
	return
		fcppt::optional::deref(
			this->secondary_weapon_
		);
}

sanguis::server::entities::with_weapon::optional_weapon_ref
sanguis::server::entities::with_weapon::get_weapon(
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

sanguis::server::weapons::optional_unique_ptr
sanguis::server::entities::with_weapon::move_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	return
		fcppt::move_clear(
			_is_primary.get()
			?
				primary_weapon_
			:
				secondary_weapon_
		);
}

sanguis::server::weapons::weapon &
sanguis::server::entities::with_weapon::set_weapon(
	sanguis::is_primary_weapon const _is_primary,
	sanguis::server::weapons::unique_ptr &&_other
)
{
	sanguis::server::weapons::weapon &ref(
		*_other
	);

	if(
		_is_primary.get()
	)
	{
		primary_weapon_ =
			sanguis::server::weapons::optional_unique_ptr(
				std::move(
					_other
				)
			);
	}
	else
	{
		secondary_weapon_ =
			sanguis::server::weapons::optional_unique_ptr(
				std::move(
					_other
				)
			);
	}

	return
		ref;
}

void
sanguis::server::entities::with_weapon::update_weapon(
	sanguis::server::entities::with_weapon::optional_weapon_ref const &_opt_weapon
)
{
	fcppt::optional::maybe_void(
		_opt_weapon,
		[](
			fcppt::reference<
				sanguis::server::weapons::weapon
			> const _weapon
		)
		{
			_weapon.get().update();
		}
	);
}

void
sanguis::server::entities::with_weapon::tick_weapon(
	sanguis::duration const &_duration,
	sanguis::server::entities::with_weapon::optional_weapon_ref const &_opt_weapon
)
{
	fcppt::optional::maybe_void(
		_opt_weapon,
		[
			_duration
		](
			fcppt::reference<
				sanguis::server::weapons::weapon
			> const _weapon
		)
		{
			_weapon.get().tick(
				_duration
			);
		}
	);
}

void
sanguis::server::entities::with_weapon::weapon_changed(
	sanguis::is_primary_weapon const _is_primary
)
{
	fcppt::optional::maybe_void(
		this->environment(),
		[
			_is_primary,
			this
		](
			fcppt::reference<
				sanguis::server::environment::object
			> const _environment
		)
		{
			if(
				_is_primary.get()
			)
			{
				_environment.get().weapon_changed(
					this->id(),
					this->primary_weapon_type()
				);
			}
		}
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

void
sanguis::server::entities::with_weapon::on_magazine_remaining(
	sanguis::is_primary_weapon,
	sanguis::magazine_remaining
)
{
}

void
sanguis::server::entities::with_weapon::on_reload_time(
	sanguis::is_primary_weapon,
	sanguis::duration
)
{
}
