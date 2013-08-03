#ifndef SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED

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
public:
	sanguis::server::weapons::unique_ptr
	replace_weapon(
		sanguis::server::weapons::unique_ptr &&
	);

	void
	target(
		sanguis::server::weapons::target
	);

	sanguis::server::weapons::target const
	target() const;

	void
	use_primary(
		bool
	);

	void
	use_secondary(
		bool
	);

	sanguis::server::entities::property::always_max &
	attack_speed();

	sanguis::server::entities::property::always_max &
	reload_speed();

	sanguis::server::weapons::ias const
	ias() const;

	sanguis::server::weapons::irs const
	irs() const;
private:
	// TODO: Replace pointers!
	void
	use_weapon(
		sanguis::server::weapons::weapon *,
		bool
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
