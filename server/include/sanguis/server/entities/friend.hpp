#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include <sanguis/friend_type.hpp>
#include <sanguis/collision/world/group_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class friend_
:
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_ai,
	public sanguis::server::entities::with_buffs,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_links,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		friend_
	);
public:
	friend_(
		sanguis::friend_type,
		sanguis::server::environment::load_context &,
		sanguis::server::damage::armor_array const &,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&
	);
private:
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	void
	update()
	override;

	sanguis::server::team
	team() const
	override;

	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::collision::world::group
	collision_group() const
	override;

	sanguis::friend_type const friend_type_;
};

}
}
}

#endif
