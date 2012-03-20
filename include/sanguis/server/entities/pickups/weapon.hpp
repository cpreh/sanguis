#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
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
	public pickup
{
	FCPPT_NONCOPYABLE(
		weapon
	);
public:
	weapon(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		server::environment::load_context &,
		server::team::type team,
		weapon_type::type
	);

	~weapon();

	weapon_type::type
	wtype() const;
private:
	messages::auto_ptr
	add_message(
		player_id
	) const;

	void
	do_pickup(
		base &receiver
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	weapon_type::type const weapon_type_;
};

}
}
}
}

#endif
