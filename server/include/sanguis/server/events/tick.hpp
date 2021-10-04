#ifndef SANGUIS_SERVER_EVENTS_TICK_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_TICK_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/server/events/tick_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::events
{

class tick
:
	public boost::statechart::event<
		tick
	>
{
public:
	tick(
		sanguis::duration const &,
		sanguis::slowdown
	);

	tick(
		tick &&
	)
	noexcept;

	tick(
		tick const &
	);

	tick &
	operator=(
		tick &&
	)
	noexcept;

	tick &
	operator=(
		tick const &
	);

	~tick()
	override;

	[[nodiscard]]
	sanguis::duration const &
	delta() const;

	[[nodiscard]]
	sanguis::slowdown
	slowdown() const;
private:
	sanguis::duration delta_;

	sanguis::slowdown slowdown_;
};

}

#endif
