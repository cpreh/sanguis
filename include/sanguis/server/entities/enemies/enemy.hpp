#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/probability.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
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
	private body_velocity_combiner,
	public with_ai,
	public with_body,
	public with_buffs,
	public with_health,
	public with_velocity
{
	FCPPT_NONCOPYABLE(
		enemy
	);
public:
	enemy(
		sanguis::diff_clock const &,
		enemy_type::type,
		server::environment::load_context &,
		damage::armor const &,
		server::health,
		entities::movement_speed,
		ai::create_function const &,
		weapons::unique_ptr weapon,
		server::probability spawn_chance,
		server::exp,
		auto_weak_link spawn_owner = auto_weak_link()
	);

	~enemy();

	enemy_type::type
	etype() const;
private:
	void
	on_update();

	messages::auto_ptr
	add_message(
		player_id
	) const;

	entity_type::type
	type() const;

	server::team::type
	team() const;

	void
	on_remove();

	enemy_type::type const etype_;

	server::probability const spawn_chance_;

	server::exp const exp_;

	auto_weak_link const spawn_owner_;
};

}
}
}
}

#endif
