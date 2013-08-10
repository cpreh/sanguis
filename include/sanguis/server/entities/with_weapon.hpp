#ifndef SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


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
	explicit
	with_weapon(
		sanguis::server::weapons::unique_ptr &&start_weapon
	);

	~with_weapon();

	virtual
	void
	on_update()
	override;

	sanguis::optional_primary_weapon_type const
	primary_weapon_type() const;
public:
	bool
	can_pickup(
		sanguis::server::weapons::weapon const &
	) const;

	void
	pickup_weapon(
		sanguis::server::weapons::unique_ptr &&
	);

	sanguis::server::weapons::unique_ptr
	drop_weapon(
		sanguis::is_primary_weapon
	);

	void
	target(
		sanguis::server::weapons::target
	);

	sanguis::server::weapons::target const
	target() const;

	void
	use_weapon(
		bool,
		sanguis::is_primary_weapon
	);

	sanguis::server::entities::property::always_max &
	attack_speed();

	sanguis::server::entities::property::always_max &
	reload_speed();

	sanguis::server::weapons::ias const
	ias() const;

	sanguis::server::weapons::irs const
	irs() const;

	void
	attacking(
		bool,
		sanguis::weapon_type
	);

	void
	reloading(
		bool,
		sanguis::weapon_type
	);
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
	is_primary_to_optional_weapon(
		sanguis::is_primary_weapon
	) const;

	sanguis::server::weapons::unique_ptr &
	is_primary_to_weapon_unique_ptr(
		sanguis::is_primary_weapon
	);

	void
	update_weapon(
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

	sanguis::server::weapons::unique_ptr primary_weapon_;

	sanguis::server::weapons::unique_ptr secondary_weapon_;

	typedef fcppt::optional<
		sanguis::server::weapons::target
	> optional_target;

	optional_target target_;

	sanguis::server::entities::property::always_max
		attack_speed_,
		reload_speed_;
};

}
}
}

#endif
