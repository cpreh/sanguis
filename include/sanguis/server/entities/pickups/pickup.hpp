#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/pickup_type.hpp>
#include <fcppt/optional_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>

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
		sanguis::diff_clock const &,
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

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif