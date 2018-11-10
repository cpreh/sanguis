#ifndef SANGUIS_CLIENT_EVENTS_TICK_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_TICK_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace events
{

class tick
:
	public boost::statechart::event<
		sanguis::client::events::tick
	>
{
public:
	explicit
	tick(
		sanguis::duration const &
	);

	tick(
		tick &&
	);

	tick(
		tick const &
	);

	tick &
	operator=(
		tick &&
	);

	tick &
	operator=(
		tick const &
	);

	~tick()
	override;

	sanguis::duration const &
	delta() const;
private:
	sanguis::duration delta_;
};

}
}
}

#endif
