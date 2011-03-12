#ifndef SANGUIS_MESSAGES_CALL_DISPATCHER_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCHER_HPP_INCLUDED

#include "dispatcher_base.hpp"
#include "../base.hpp"
#include "../concrete.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace call
{

template<
	typename Callee,
	typename Message
>
class dispatcher
:
	public dispatcher_base<
		Callee
	>
{
	FCPPT_NONCOPYABLE(
		dispatcher
	);
public:
	dispatcher()
	{
	}

	~dispatcher()
	{
	}

	typename Callee::result_type
	call(
		Callee &_callee,
		base const &_message
	) const
	{
		return
			_callee(
				dynamic_cast<
					concrete<
						Message
					> const &
				>(
					_message
				).value()
			);
	}
};

}
}
}

#endif
