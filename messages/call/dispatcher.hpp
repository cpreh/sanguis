#ifndef SANGUIS_MESSAGES_CALL_DISPATCHER_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCHER_HPP_INCLUDED

#include "dispatcher_base.hpp"
#include "../base.hpp"
#include "../concrete.hpp"

namespace sanguis
{
namespace messages
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
public:
	typename Callee::result_type
	call(
		Callee &callee_,
		base const &message_
	) const
	{
		return
			callee_(
				dynamic_cast<
					concrete<
						Message
					> const &
				>(
					message_
				).value()
			);
	}
};

}
}

#endif
