#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_RELOAD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_RELOAD_HPP_INCLUDED

#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/reload_fwd.hpp>
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

class reload
:
	public boost::statechart::event<
		sanguis::server::weapons::events::reload
	>
{
	FCPPT_NONASSIGNABLE(
		reload
	);
public:
	explicit
	reload(
		sanguis::server::entities::with_weapon &
	);

	sanguis::server::entities::with_weapon &
	from() const;
private:
	sanguis::server::entities::with_weapon &from_;
};

}
}
}
}

#endif
