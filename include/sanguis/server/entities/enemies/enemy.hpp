#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
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
	enemy(
		sanguis::diff_clock const &,
		sanguis::creator::enemy_type,
		sanguis::server::environment::load_context &,
		sanguis::server::damage::armor const &,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::pickup_probability,
		sanguis::server::exp,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::entities::enemies::spawn_owner const &,
		sanguis::server::auras::container &&
	);

	~enemy();

	sanguis::creator::enemy_type
	etype() const;

	sanguis::server::team
	team() const
	override;
private:
	void
	update()
	override;

	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::collision::world::group_field const
	collision_groups() const
	override;

	void
	remove()
	override;

	sanguis::creator::enemy_type const etype_;

	sanguis::server::pickup_probability const spawn_chance_;

	sanguis::server::exp const exp_;

	sanguis::server::entities::enemies::difficulty const difficulty_;

	sanguis::server::entities::enemies::spawn_owner const spawn_owner_;
};

}
}
}
}

#endif
