#ifndef SANGUIS_SERVER_WEAPONS_STATES_IDLE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_IDLE_HPP_INCLUDED

#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/reload_fwd.hpp>
#include <sanguis/server/weapons/events/shoot_fwd.hpp>
#include <sanguis/server/weapons/states/idle_fwd.hpp>
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

class idle
:
	public boost::statechart::state<
		sanguis::server::weapons::states::idle,
		sanguis::server::weapons::weapon
	>
{
	FCPPT_NONCOPYABLE(
		idle
	);
public:
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::shoot
		>,
		boost::statechart::custom_reaction<
			sanguis::server::weapons::events::reload
		>
	> reactions;

	explicit
	idle(
		my_context
	);

	virtual
	~idle()
	override;

	boost::statechart::result
	react(
		sanguis::server::weapons::events::shoot const &
	);

	boost::statechart::result
	react(
		sanguis::server::weapons::events::reload const &
	);
};

}
}
}
}

#endif
