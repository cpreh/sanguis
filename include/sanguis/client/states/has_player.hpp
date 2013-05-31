#ifndef SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED

#include <sanguis/client/states/running.hpp>
#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/client/control/action_handler_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/messages/available_perks.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/give_weapon.hpp>
#include <sanguis/messages/level_up.hpp>
#include <sanguis/messages/remove_id.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>
#include <fcppt/config/external_end.hpp>


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
	);
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

	virtual ~has_player();

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
		messages::available_perks const &
	);

	result_type
	operator()(
		messages::give_weapon const &
	);

	result_type
	operator()(
		messages::level_up const &
	);

	result_type
	operator()(
		messages::remove_id const &
	);

	perk::state &
	perk_state();
private:
	boost::statechart::result
	handle_default_msg(
		sanguis::messages::base const &
	);

	void
	send_perk_choose(
		sanguis::perk_type
	);

	fcppt::scoped_ptr<
		control::action_handler
	> action_handler_;

	fcppt::scoped_ptr<
		perk::state
	> perk_state_;
};

}
}
}

#endif

