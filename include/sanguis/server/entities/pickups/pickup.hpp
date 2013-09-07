#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/collision/world/group_vector.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
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
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_links
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
		sanguis::server::team
	);
private:
	bool
	dead() const
	override;

	sanguis::server::team
	team() const
	override;

	boost::logic::tribool const
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const
	override;

	void
	collision_with_body(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::collision::world::group_vector
	collision_groups() const
	override;

	virtual
	void
	do_pickup(
		sanguis::server::entities::base &receiver
	) = 0;

	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::server::team const team_;

	sanguis::pickup_type const ptype_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
