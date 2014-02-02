#ifndef SANGUIS_MESSAGES_CALL_DISPATCH_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCH_HPP_INCLUDED

#include <sanguis/messages/call/dispatch_visitor.hpp>
#include <sanguis/messages/call/result.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace call
{

template<
	typename Dispatcher,
	typename Function,
	typename Event,
	typename HandleDefaultMsg
>
boost::statechart::result
dispatch(
	Dispatcher &_dispatcher,
	Function &_function,
	Event const &_message,
	HandleDefaultMsg const &_handle_default_msg
)
{
	// TODO: Refactor alda's default msg so this isn't necessary
	auto const fake_default_msg(
		[
			_handle_default_msg
		](
			typename Dispatcher::message_base const &_message_base
		)
		{
			return
				sanguis::messages::call::result(
					_handle_default_msg(
						_message_base
					)
				);
		}
	);

	return
		fcppt::variant::apply_unary(
			sanguis::messages::call::dispatch_visitor<
				Event,
				HandleDefaultMsg
			>(
				_message,
				_handle_default_msg
			),
			_dispatcher(
				*_message.get(),
				_function,
				fake_default_msg
			).get()
		);
}

}
}
}

#endif
