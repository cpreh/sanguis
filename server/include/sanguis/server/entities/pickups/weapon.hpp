#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/weapon_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/optional_unique_ptr.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class weapon
:
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_links
{
	FCPPT_NONCOPYABLE(
		weapon
	);
public:
	weapon(
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::weapons::unique_ptr &&
	);

	~weapon()
	override;

	sanguis::server::weapons::unique_ptr
	obtain();

	sanguis::weapon_type const
	weapon_type() const;
private:
	bool
	dead() const
	override;

	sanguis::server::team
	team() const
	override;

	sanguis::collision::world::body_group
	collision_group() const
	override;

	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id,
		sanguis::collision::world::created
	) const
	override;

	sanguis::server::weapons::weapon &
	get() const;

	sanguis::server::team const team_;

	sanguis::server::weapons::optional_unique_ptr weapon_;
};

}
}
}
}

#endif
