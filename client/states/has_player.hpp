#ifndef SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED

#include "running.hpp"
#include "ingame_fwd.hpp"
#include "../control/input_translator_fwd.hpp"
#include "../control/action_handler_fwd.hpp"
#include "../control/player_action_fwd.hpp"
#include "../events/message_fwd.hpp"
#include "../events/action_fwd.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../messages/remove_id.hpp"
#include "../../messages/give_weapon.hpp"
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
		running,
		ingame
	>
{
	FCPPT_NONCOPYABLE(
		has_player
	)
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::message
		>,
		boost::statechart::custom_reaction<
			events::action
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
		events::action const &
	);

	typedef boost::statechart::result result_type;

	result_type
	operator()(
		messages::give_weapon const &
	);

	result_type
	operator()(
		messages::remove_id const &
	);
private:
	void
	handle_player_action(
		control::player_action const &
	);

	boost::statechart::result
	handle_default_msg(
		sanguis::messages::base const &
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

