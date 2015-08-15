#ifndef SANGUIS_CLIENT_DISPATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DISPATCH_HPP_INCLUDED

#include <sanguis/client/dispatch_default_function.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/messages/call/dispatch.hpp>
#include <sanguis/messages/server/call/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
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
	sanguis::client::dispatch_default_function const &_handle_default_msg
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
