#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/weapon_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

// TODO: This is a new class of pickups that aren't picked up automatically.
// Maybe we should create a new base class for this!
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

	~weapon();

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

	sanguis::collision::world::group_field const
	collision_groups() const
	override;

	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::server::team const team_;

	sanguis::server::weapons::unique_ptr weapon_;
};

}
}
}
}

#endif
