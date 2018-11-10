#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_RELOAD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_RELOAD_HPP_INCLUDED

#include <sanguis/server/weapons/events/reload_fwd.hpp>
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
public:
	reload();

	reload(
		reload &&
	);

	reload(
		reload const &
	);

	reload &
	operator=(
		reload &&
	);

	reload &
	operator=(
		reload const &
	);

	~reload()
	override;
};

}
}
}
}

#endif
