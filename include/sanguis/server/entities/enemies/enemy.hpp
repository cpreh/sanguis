#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
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
	private sanguis::server::entities::body_velocity_combiner,
	public sanguis::server::entities::with_ai,
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_buffs,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		enemy
	);
public:
	enemy(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::enemy_type,
		sanguis::server::environment::load_context &,
		sanguis::server::damage::armor const &,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&,
		sanguis::server::pickup_probability,
		sanguis::server::exp,
		sanguis::server::entities::enemies::spawn_owner const &
	);

	~enemy();

	sanguis::enemy_type
	etype() const;
private:
	void
	on_update()
	override;

	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::server::collision::group_vector
	collision_groups() const
	override;

	sanguis::server::team
	team() const
	override;

	void
	on_remove()
	override;

	sanguis::enemy_type const etype_;

	sanguis::server::pickup_probability const spawn_chance_;

	sanguis::server::exp const exp_;

	sanguis::server::entities::enemies::spawn_owner const spawn_owner_;
};

}
}
}
}

#endif
