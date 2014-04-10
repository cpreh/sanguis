#ifndef SANGUIS_MESSAGES_CALL_DISPATCH_VISITOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCH_VISITOR_HPP_INCLUDED

#include <sanguis/messages/call/forward_to_default.hpp>
#include <fcppt/nonassignable.hpp>
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
	typename Event,
	typename HandleDefaultMsg
>
class dispatch_visitor
{
	FCPPT_NONASSIGNABLE(
		dispatch_visitor
	);
public:
	dispatch_visitor(
		Event const &_event,
		HandleDefaultMsg const &_handle_default_msg
	)
	:
		event_(
			_event
		),
		handle_default_msg_(
			_handle_default_msg
		)
	{
	}

	typedef
	boost::statechart::result
	result_type;

	result_type
	operator()(
		boost::statechart::result const _result
	) const
	{
		return
			_result;
	}

	result_type
	operator()(
		sanguis::messages::call::forward_to_default
	) const
	{
		return
			handle_default_msg_(
				*event_.get()
			);
	}
private:
	Event const event_;

	HandleDefaultMsg const handle_default_msg_;
};

}
}
}

#endif
