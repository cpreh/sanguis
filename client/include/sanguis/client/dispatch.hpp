#ifndef SANGUIS_CLIENT_DISPATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DISPATCH_HPP_INCLUDED

#include <sanguis/client/events/message.hpp>
#include <sanguis/messages/call/dispatch.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/call/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

template<
	typename MessageTypes,
	typename State
>
boost::statechart::result
dispatch(
	State &_state,
	sanguis::client::events::message const &_message,
	std::function<
		boost::statechart::result (
			sanguis::messages::server::base const &
		)
	> const _handle_default_msg
)
{
	static
	sanguis::messages::server::call::object<
		MessageTypes,
		State
	>
	dispatcher;

	return
		sanguis::messages::call::dispatch(
			dispatcher,
			_state,
			_message,
			_handle_default_msg
		);
}

}
}

#endif
