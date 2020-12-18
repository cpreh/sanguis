#ifndef SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED

#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/client/info_fwd.hpp>
#include <sanguis/messages/client/pause_fwd.hpp>
#include <sanguis/messages/client/unpause_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/states/running.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object.hpp>
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
namespace states
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

class paused
:
	public
		boost::statechart::state<
			sanguis::server::states::paused,
			sanguis::server::states::running
		>
{
	FCPPT_NONCOPYABLE(
		paused
	);
public:
	using
	reactions
	=
	boost::mpl::list1<
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>
	>;

	explicit
	paused(
		my_context
	);

	~paused();

	// reactions
	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::info const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::unpause const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::pause const &
	);
private:
	boost::statechart::result
	unpause_impl();

	fcppt::log::object log_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
