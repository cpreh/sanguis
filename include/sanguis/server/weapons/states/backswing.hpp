#ifndef SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <sanguis/server/weapons/states/backswing_fwd.hpp>
#include <sanguis/server/weapons/states/backswing_parameters_fwd.hpp>
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

class backswing
:
	public boost::statechart::state<
		sanguis::server::weapons::states::backswing,
		sanguis::server::weapons::weapon
	>
{
	FCPPT_NONCOPYABLE(
		backswing
	);
public:
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::poll
		>,
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::stop
		>
	> reactions;

	backswing(
		my_context,
		sanguis::server::weapons::states::backswing_parameters const &
	);

	virtual
	~backswing();

	boost::statechart::result
	react(
		sanguis::server::weapons::events::poll const &
	);

	boost::statechart::result
	react(
		sanguis::server::weapons::events::stop const &
	);
private:
	bool cancelled_;

	sanguis::diff_timer cooldown_;
};

}
}
}
}

#endif
