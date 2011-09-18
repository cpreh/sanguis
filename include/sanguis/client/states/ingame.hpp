#ifndef SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED

#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/cursor/scoped.hpp>
#include <fcppt/noncopyable.hpp>
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

class ingame
:
	public boost::statechart::state<
		ingame,
		has_player
	>
{
	FCPPT_NONCOPYABLE(
		ingame
	);
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::action
		>
	> reactions;

	explicit ingame(
		my_context
	);

	virtual ~ingame();

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		events::action const &
	);
private:
	client::cursor::scoped const scoped_cursor_;
};

}
}
}

#endif
