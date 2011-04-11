#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include "../base_fwd.hpp"
#include "../with_body.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../dim.hpp"
#include "../../team.hpp"
#include "../../../pickup_type.hpp"
#include "../../../diff_clock.hpp"
#include "../../../messages/auto_ptr.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/optional_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class pickup
:
	public entities::with_body
{
	FCPPT_NONCOPYABLE(
		pickup
	);
public:
	pickup_type::type
	ptype() const;

	virtual ~pickup();
protected:
	typedef fcppt::optional<
		server::dim
	> optional_dim;

	pickup(
		pickup_type::type,
		server::environment::load_context &,
		team::type,
		optional_dim const &
	);
private:
	bool
	dead() const;

	entity_type::type
	type() const;

	server::team::type
	team() const;

	boost::logic::tribool const
	can_collide_with_body(
		entities::with_body const &
	) const;

	void
	collision_with_body(
		entities::with_body &
	);

	void
	on_update(
		time_type
	);
	
	virtual void
	do_pickup(
		entities::base &receiver
	) = 0;

	messages::auto_ptr
	add_message(
		player_id
	) const;

	server::team::type const team_;

	pickup_type::type const ptype_;

	diff_clock diff_clock_;

	sge::time::timer life_timer_;
};

}
}
}
}

#endif
