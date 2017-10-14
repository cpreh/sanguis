#ifndef SANGUIS_CLIENT_STATES_CONSOLE_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_CONSOLE_HPP_INCLUDED

#include <sanguis/client/scoped_pause.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/events/input_fwd.hpp>
#include <sanguis/client/events/overlay_fwd.hpp>
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

class console
:
	public boost::statechart::state<
		sanguis::client::states::console,
		sanguis::client::states::has_player
	>
{
	FCPPT_NONCOPYABLE(
		console
	);
public:
	typedef
	boost::mpl::list3<
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::overlay
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::input
		>
	>
	reactions;

	explicit
	console(
		my_context
	);

	~console()
	override;

	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::overlay const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::input const &
	);
private:
	sanguis::client::scoped_pause const pause_;
};

}
}
}

#endif
