#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED

#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/shoot_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace events
{

class shoot
:
	public boost::statechart::event<
		sanguis::server::weapons::events::shoot
	>
{
	FCPPT_NONASSIGNABLE(
		shoot
	);
public:
	shoot(
		sanguis::server::entities::with_weapon &from,
		sanguis::server::vector const &to
	);

	sanguis::server::entities::with_weapon &
	from() const;

	sanguis::server::vector const &
	to() const;
private:
	sanguis::server::entities::with_weapon &from_;

	sanguis::server::vector const to_;
};

}
}
}
}

#endif
