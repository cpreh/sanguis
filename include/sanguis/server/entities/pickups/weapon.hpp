#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class weapon
:
	public sanguis::server::entities::pickups::pickup
{
	FCPPT_NONCOPYABLE(
		weapon
	);
public:
	weapon(
		sanguis::diff_clock const &,
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::weapons::unique_ptr &&
	);

	~weapon();
private:
	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	void
	do_pickup(
		sanguis::server::entities::base &receiver
	)
	override;

	sanguis::server::weapons::unique_ptr weapon_;
};

}
}
}
}

#endif
