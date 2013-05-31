#ifndef SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED

#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/messages/add_own_player.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace states
{

class waiting_for_player
:
	public boost::statechart::state<
		sanguis::client::states::waiting_for_player,
		sanguis::client::states::running
	>
{
	FCPPT_NONCOPYABLE(
		waiting_for_player
	);
public:
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::client::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>
	> reactions;

	explicit
	waiting_for_player(
		my_context
	);

	virtual
	~waiting_for_player();

	boost::statechart::result
	react(
		sanguis::client::events::message const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);

	typedef boost::statechart::result result_type;

	result_type
	operator()(
		sanguis::messages::add_own_player const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		sanguis::messages::base const &
	);
};

}
}
}

#endif
