#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/entity_type_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
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
	private sanguis::server::entities::body_velocity_combiner,
	public sanguis::server::entities::with_ai,
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_buffs,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		friend_
	);
public:
	friend_(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::friend_type,
		sanguis::server::environment::load_context &,
		sanguis::server::damage::armor const &,
		sanguis::server::health,
		sanguis::server::entities::movement_speed,
		sanguis::server::ai::create_function const &,
		sanguis::server::weapons::unique_ptr &&
	);
private:
	void
	on_update();

	sanguis::entity_type
	type() const;

	sanguis::server::team
	team() const;

	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const;

	sanguis::friend_type const ftype_;
};

}
}
}

#endif
