#ifndef SANGUIS_SERVER_ENTITIES_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class destructible
:
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_links,
	public virtual sanguis::server::entities::ifaces::with_team
{
	FCPPT_NONCOPYABLE(
		destructible
	);
public:
	destructible(
		sanguis::creator::destructible_type,
		sanguis::server::environment::load_context &,
		sanguis::server::health,
		sanguis::server::damage::armor_array const &,
		sanguis::server::entities::enemies::difficulty
	);

	~destructible()
	override;
private:
	void
	update()
	override;

	void
	remove_from_game()
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

	sanguis::creator::destructible_type const type_;

	sanguis::server::entities::enemies::difficulty const difficulty_;
};

}
}
}

#endif
