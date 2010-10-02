#ifndef SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED

#include "../control/input_translator_fwd.hpp"
#include "../control/action_handler_fwd.hpp"
#include "../events/message_fwd.hpp"
#include "../events/player_action_fwd.hpp"
#include "../../messages/remove_id.hpp"
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list/list10.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class has_player
:
	public boost::statechart::state<
		has_player,
		running
	>
{
	FCPPT_NONCOPYABLE(
		has_player
	)
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reacton<
			events::message
		>,
		boost::statechart::custom_reacton<
			events::player_action
		>
	> reactions;

	explicit has_player(
		my_context
	);

	~has_player();

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	react(
		events::player_action const &
	);

	boost::statechart::result
	operator()(
		messages::remove_id const &
	);
private:
	void
	handle_player_action(
		control::player_action const &
	);

	fcppt::scoped_ptr<
		control::input_translator
	> input_translator_;

	fcppt::scoped_ptr<
		control::action_handler
	> action_handler_;
};

}
}
}

#endif

