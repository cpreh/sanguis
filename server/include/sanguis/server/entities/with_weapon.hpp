#ifndef SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/server/damage/basic_array.hpp>
#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/weapons/const_optional_ref_fwd.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_weapon
:
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_angle,
	public virtual sanguis::server::entities::ifaces::with_id,
	public virtual sanguis::server::entities::ifaces::with_team
{
	FCPPT_NONCOPYABLE(
		with_weapon
	);
protected:
	with_weapon(
		sanguis::server::weapons::optional_unique_ptr &&,
		sanguis::server::weapons::ias,
		sanguis::server::weapons::irs
	);

	~with_weapon()
	override;

	void
	update()
	override;

	void
	tick(
		sanguis::duration const &
	)
	override;

	sanguis::optional_primary_weapon_type const
	primary_weapon_type() const;
public:
	void
	pickup_weapon(
		sanguis::server::weapons::unique_ptr &&
	);

	sanguis::server::weapons::optional_unique_ptr
	drop_weapon(
		sanguis::is_primary_weapon
	);

	void
	target(
		sanguis::server::weapons::optional_target
	);

	sanguis::server::weapons::optional_target const
	target() const;

	bool
	in_range(
		sanguis::is_primary_weapon
	) const;

	void
	use_weapon(
		bool,
		sanguis::is_primary_weapon
	);

	void
	reload(
		sanguis::is_primary_weapon
	);

	sanguis::server::entities::property::always_max &
	attack_speed();

	sanguis::server::entities::property::always_max &
	reload_speed();

	sanguis::server::entities::property::always_max &
	extra_damage(
		sanguis::server::damage::type
	);

	sanguis::server::damage::unit const
	extra_damage_value(
		sanguis::server::damage::type
	) const;

	sanguis::server::weapons::ias const
	ias() const;

	sanguis::server::weapons::irs const
	irs() const;

	sanguis::server::weapons::const_optional_ref const
	primary_weapon() const;

	sanguis::server::weapons::const_optional_ref const
	secondary_weapon() const;

	void
	weapon_status(
		sanguis::weapon_status,
		sanguis::server::weapons::weapon const &
	);

	void
	reload_time(
		sanguis::duration,
		sanguis::server::weapons::weapon const &
	);

	void
	magazine_remaining(
		sanguis::magazine_remaining,
		sanguis::server::weapons::weapon const &
	);

	sanguis::weapon_status
	weapon_status() const;
private:
	typedef
	fcppt::optional<
		sanguis::server::weapons::weapon &
	>
	optional_weapon_ref;

	sanguis::server::entities::with_weapon::optional_weapon_ref const
	primary_weapon_ref() const;

	sanguis::server::entities::with_weapon::optional_weapon_ref const
	secondary_weapon_ref() const;

	sanguis::server::entities::with_weapon::optional_weapon_ref const
	weapon_ref(
		sanguis::server::weapons::optional_unique_ptr const &
	) const;

	sanguis::server::entities::with_weapon::optional_weapon_ref const
	is_primary_to_optional_weapon(
		sanguis::is_primary_weapon
	) const;

	sanguis::server::weapons::optional_unique_ptr &
	is_primary_to_weapon_unique_ptr(
		sanguis::is_primary_weapon
	);

	void
	update_weapon(
		sanguis::server::entities::with_weapon::optional_weapon_ref const &
	);

	void
	tick_weapon(
		sanguis::duration const &,
		sanguis::server::entities::with_weapon::optional_weapon_ref const &
	);

	void
	weapon_changed(
		sanguis::is_primary_weapon
	);

	virtual
	void
	on_new_weapon(
		sanguis::server::weapons::weapon const &
	);

	virtual
	void
	on_drop_weapon(
		sanguis::is_primary_weapon
	);

	virtual
	void
	on_magazine_remaining(
		sanguis::is_primary_weapon,
		sanguis::magazine_remaining
	);

	virtual
	void
	on_reload_time(
		sanguis::is_primary_weapon,
		sanguis::duration
	);

	sanguis::server::weapons::optional_unique_ptr primary_weapon_;

	sanguis::server::weapons::optional_unique_ptr secondary_weapon_;

	sanguis::server::weapons::optional_target target_;

	sanguis::weapon_status weapon_status_;

	sanguis::server::entities::property::always_max
		attack_speed_,
		reload_speed_;

	typedef
	sanguis::server::damage::basic_array<
		sanguis::server::entities::property::always_max
	>
	extra_damage_array;

	extra_damage_array extra_damages_;
};

}
}
}

#endif
