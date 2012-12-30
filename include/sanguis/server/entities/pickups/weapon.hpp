#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
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
		sanguis::random_generator &,
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::weapon_type
	);

	~weapon();

	sanguis::weapon_type
	wtype() const;
private:
	sanguis::messages::auto_ptr
	add_message(
		sanguis::server::player_id
	) const;

	void
	do_pickup(
		sanguis::server::entities::base &receiver
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::weapon_type const weapon_type_;
};

}
}
}
}

#endif
