#ifndef SANGUIS_CLIENT_STATES_CONSOLE_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_CONSOLE_HPP_INCLUDED

#include <sanguis/client/scoped_pause.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/events/input_fwd.hpp>
#include <sanguis/client/events/overlay_fwd.hpp>
#include <sanguis/client/states/has_player.hpp>
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
namespace client
{
namespace states
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

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
	using
	reactions
	=
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
	>;

	explicit
	console(
		my_context
	);

	~console();

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

FCPPT_PP_POP_WARNING

}
}
}

#endif
