#ifndef SANGUIS_MESSAGES_MAKE_CALLER_INSTANCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CALLER_INSTANCE_HPP_INCLUDED

#include "dispatcher.hpp"
#include "../message_id.hpp"
#include <sge/make_auto_ptr.hpp>

namespace sanguis
{
namespace messages
{

template<
	typename Callee,
	typename InstanceArray
>
class make_caller_instance {
public:
	explicit make_caller_instance(
		InstanceArray &instances_
	)
	:
		instances_(instances_)
	{}
	
	template<
		typename Msg
	>
	void
	operator(
		Msg &
	) const
	{
		typedef call::dispatcher<
			Callee,
			Msg
		> dispatcher;

		sge::auto_ptr<
			dispatcher
		> ptr(
			sge::make_auto_ptr<
				dispatcher
			>()
		);

		instances_[
			message_id<
				Msg
			>::value
		] = ptr;
	}
private:
	InstanceArray &instances_;
};

}
}

#endif
