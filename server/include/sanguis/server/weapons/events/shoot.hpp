#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED

#include <sanguis/server/weapons/events/shoot_fwd.hpp>
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
public:
	shoot();

	shoot(
		shoot &&
	)
	noexcept;

	shoot(
		shoot const &
	);

	shoot &
	operator=(
		shoot &&
	)
	noexcept;

	shoot &
	operator=(
		shoot const &
	);

	~shoot()
	override;
};

}
}
}
}

#endif
