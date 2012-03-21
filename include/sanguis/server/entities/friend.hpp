#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class friend_
:
	private body_velocity_combiner,
	public with_ai,
	public with_body,
	public with_buffs,
	public with_health,
	public with_velocity
{
	FCPPT_NONCOPYABLE(
		friend_
	);
public:
	friend_(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		friend_type::type,
		server::environment::load_context &,
		damage::armor const &,
		server::health,
		entities::movement_speed,
		ai::create_function const &,
		weapons::unique_ptr weapon
	);
private:
	void
	on_update();

	entity_type::type
	type() const;

	server::team::type
	team() const;

	messages::auto_ptr
	add_message(
		server::player_id
	) const;

	friend_type::type const ftype_;
};

}
}
}

#endif
