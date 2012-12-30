#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/entity_type_fwd.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/pickups/optional_dim_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
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
	public sanguis::server::entities::with_body
{
	FCPPT_NONCOPYABLE(
		pickup
	);
public:
	sanguis::pickup_type
	ptype() const;

	virtual
	~pickup();
protected:
	pickup(
		sanguis::diff_clock const &,
		sanguis::pickup_type,
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::entities::pickups::optional_dim const &
	);
private:
	bool
	dead() const;

	sanguis::entity_type
	type() const;

	sanguis::server::team
	team() const;

	boost::logic::tribool const
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const;

	void
	collision_with_body(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	do_pickup(
		sanguis::server::entities::base &receiver
	) = 0;

	sanguis::messages::auto_ptr
	add_message(
		sanguis::server::player_id
	) const;

	sanguis::server::team const team_;

	sanguis::pickup_type const ptype_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
