#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include "pickup.hpp"
#include "../base_fwd.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../team.hpp"
#include "../../../messages/auto_ptr.hpp"
#include "../../../diff_clock_fwd.hpp"
#include "../../../weapon_type.hpp"
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

	weapon_type::type const weapon_type_;
};

}
}
}
}

#endif
