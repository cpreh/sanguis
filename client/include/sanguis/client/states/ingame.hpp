#ifndef SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED

#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame_fwd.hpp>
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
	using
	reactions
	=
	boost::mpl::list1<
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>
	>;

	explicit
	ingame(
		my_context
	);

	~ingame();

	using
	result_type
	=
	boost::statechart::result;

	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
