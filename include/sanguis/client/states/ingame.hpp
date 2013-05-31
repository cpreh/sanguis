#ifndef SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED

#include <sanguis/client/cursor/scoped.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/client/states/has_player.hpp>
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

class ingame
:
	public boost::statechart::state<
		sanguis::client::states::ingame,
		sanguis::client::states::has_player
	>
{
	FCPPT_NONCOPYABLE(
		ingame
	);
public:
	typedef boost::mpl::list1<
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>
	> reactions;

	explicit
	ingame(
		my_context
	);

	virtual
	~ingame();

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);
private:
	sanguis::client::cursor::scoped const scoped_cursor_;
};

}
}
}

#endif
