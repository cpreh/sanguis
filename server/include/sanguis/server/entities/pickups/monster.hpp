#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED

#include <sanguis/friend_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class monster
:
	public sanguis::server::entities::pickups::pickup
{
	FCPPT_NONCOPYABLE(
		monster
	);
public:
	monster(
		sanguis::random_generator &,
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::friend_type,
		sanguis::server::entities::enemies::difficulty
	);

	~monster();
private:
	void
	do_pickup(
		sanguis::server::entities::base &receiver
	)
	override;

	sanguis::random_generator &random_generator_;

	sanguis::friend_type const friend_type_;

	sanguis::server::entities::enemies::difficulty const difficulty_;
};

}
}
}
}

#endif
