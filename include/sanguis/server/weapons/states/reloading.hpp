#ifndef SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <sanguis/server/weapons/events/reset_fwd.hpp>
#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <sanguis/server/weapons/states/reloading_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
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
		sanguis::server::weapons::states::reloading,
		sanguis::server::weapons::weapon
	>
{
	FCPPT_NONCOPYABLE(
		reloading
	);
public:
	typedef boost::mpl::list3<
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::poll
		>,
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::stop
		>,
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::reset
		>
	> reactions;

	explicit
	reloading(
		my_context
	);

	virtual
	~reloading();

	boost::statechart::result
	react(
		sanguis::server::weapons::events::poll const &
	);

	boost::statechart::result
	react(
		sanguis::server::weapons::events::stop const &
	);

	boost::statechart::result
	react(
		sanguis::server::weapons::events::reset const &
	);
private:
	sanguis::diff_timer reload_time_;
};

}
}
}
}

#endif
