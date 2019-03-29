#ifndef SANGUIS_SERVER_WEAPONS_STATES_CASTPOINT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_CASTPOINT_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <sanguis/server/weapons/states/castpoint_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

class castpoint
:
	public boost::statechart::state<
		sanguis::server::weapons::states::castpoint,
		sanguis::server::weapons::weapon
	>
{
	FCPPT_NONCOPYABLE(
		castpoint
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

	explicit
	castpoint(
		my_context
	);

	~castpoint();

	boost::statechart::result
	react(
		sanguis::server::weapons::events::poll const &
	);

	boost::statechart::result
	react(
		sanguis::server::weapons::events::stop const &
	);
private:
	sanguis::diff_timer attack_time_;

	bool cancelled_;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
