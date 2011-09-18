#ifndef SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED

#include <sanguis/server/weapons/states/reloading_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <sanguis/server/weapons/events/reset_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class reloading
:
	public boost::statechart::state<
		reloading,
		weapon
	>
{
	FCPPT_NONCOPYABLE(
		reloading
	);
public:
	typedef boost::mpl::list3<
		boost::statechart::custom_reaction<
			events::poll
		>,
		boost::statechart::custom_reaction<
			events::stop
		>,
		boost::statechart::custom_reaction<
			events::reset
		>
	> reactions;

	explicit reloading(
		my_context
	);

	~reloading();

	boost::statechart::result
	react(
		events::poll const &
	);

	boost::statechart::result
	react(
		events::stop const &
	);

	boost::statechart::result
	react(
		events::reset const &
	);
private:
	sanguis::diff_timer reload_time_;
};

}
}
}
}

#endif
