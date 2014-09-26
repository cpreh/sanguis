#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/collision/world/group_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class enemy
:
	public sanguis::server::entities::with_ai,
	public sanguis::server::entities::with_buffs,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_links,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		enemy
	);
public:
	explicit
	enemy(
		sanguis::server::entities::enemies::parameters &&
	);

	~enemy()
	override;

	sanguis::server::team
	team() const
	override;
protected:
	void
	update()
	override;

	sanguis::creator::enemy_type
	enemy_type() const;
private:
	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::collision::world::group
	collision_group() const
	override;

	void
	remove()
	override;

	virtual
	sanguis::messages::types::string const &
	name() const = 0;

	virtual
	sanguis::enemy_kind
	enemy_kind() const = 0;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::server::pickup_probability const pickup_probability_;

	sanguis::server::exp const exp_;

	sanguis::server::entities::enemies::difficulty const difficulty_;

	sanguis::server::entities::spawn_owner const spawn_owner_;
};

}
}
}
}

#endif
