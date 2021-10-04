#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/mass.hpp>
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
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::enemies
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
	FCPPT_NONMOVABLE(
		enemy
	);
public:
	explicit
	enemy(
		sanguis::server::entities::enemies::parameters &&
	);

	~enemy()
	override;

	[[nodiscard]]
	sanguis::server::team
	team() const
	override;

	[[nodiscard]]
	sanguis::creator::enemy_type
	enemy_type() const;

	[[nodiscard]]
	sanguis::server::exp
	exp() const;

	[[nodiscard]]
	sanguis::server::mass
	mass() const;

	[[nodiscard]]
	sanguis::server::entities::enemies::difficulty
	difficulty() const;
protected:
	void
	update()
	override;

	void
	remove_from_game()
	override;
private:
	[[nodiscard]]
	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id,
		sanguis::collision::world::created
	) const
	override;

	[[nodiscard]]
	sanguis::collision::world::body_group
	collision_group() const
	override;

	[[nodiscard]]
	virtual
	sanguis::messages::types::string const &
	name() const = 0;

	[[nodiscard]]
	virtual
	sanguis::enemy_kind
	enemy_kind() const = 0;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::server::pickup_probability const pickup_probability_;

	sanguis::server::exp const exp_;

	sanguis::server::mass const mass_;

	sanguis::server::entities::enemies::difficulty const difficulty_;

	sanguis::server::entities::spawn_owner const spawn_owner_;
};

}

#endif
