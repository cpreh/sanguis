#ifndef SANGUIS_MESSAGES_CALL_MAKE_INSTANCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_MAKE_INSTANCE_HPP_INCLUDED

#include "dispatcher.hpp"
#include "../message_id.hpp"
#include <fcppt/make_auto_ptr.hpp>

namespace sanguis
{
namespace messages
{
namespace call
{

template<
	typename Callee,
	typename InstanceArray
>
class make_instance {
public:
	explicit make_instance(
		InstanceArray &instances_
	)
	:
		instances_(instances_)
	{}
	
	template<
		typename Msg
	>
	void
	operator()() const
	{
		typedef call::dispatcher<
			Callee,
			Msg
		> dispatcher;

		sge::auto_ptr<
			dispatcher
		> ptr(
			fcppt::make_auto_ptr<
				dispatcher
			>()
		);

		instances_. template replace<
			message_id<
				typename Msg::types
			>::type::value
		>(
			ptr
		);
	}
private:
	InstanceArray &instances_;
};

}
}
} 

#endif
