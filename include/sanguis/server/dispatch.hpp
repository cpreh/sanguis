#ifndef SANGUIS_SERVER_DISPATCH_HPP_INCLUDED
#define SANGUIS_SERVER_DISPATCH_HPP_INCLUDED

#include <sanguis/server/message_functor.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/messages/call/dispatch.hpp>
#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/messages/client/call/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

template<
	typename MessageTypes,
	typename State
>
boost::statechart::result
dispatch(
	State &_state,
	sanguis::server::events::message const &_message,
	std::function<
		boost::statechart::result (
			sanguis::server::player_id,
			sanguis::messages::client::base const &
		)
	> const _handle_default_msg
)
{
	typedef
	sanguis::server::message_functor<
		State
	>
	functor_type;

	static
	sanguis::messages::client::call::object<
		MessageTypes,
		functor_type
	>
	dispatcher;

	functor_type functor(
		_state,
		_message.id()
	);

	return
		sanguis::messages::call::dispatch(
			dispatcher,
			functor,
			_message,
			std::bind(
				_handle_default_msg,
				_message.id(),
				std::placeholders::_1
			)
		);
}

}
}

#endif
