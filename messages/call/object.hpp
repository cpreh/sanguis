#ifndef SANGUIS_MESSAGES_CALL_OBJECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_OBJECT_HPP_INCLUDED

#include "default_function.hpp"
#include "dispatcher_base.hpp"
#include "make_instance.hpp"
#include "../base_fwd.hpp"
#include "../types/message.hpp"
#include <sge/mpl/for_each.hpp>
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_array.hpp>

namespace sanguis
{
namespace messages
{
namespace call
{

template<
	typename Messages,
	typename Callee
>
class object {
	SGE_NONCOPYABLE(object)

	typedef typename Callee::result_type result_type;

	typedef call::dispatcher_base<
		Callee
	> dispatcher_base;

	typedef boost::ptr_array<
		dispatcher_base,
		types::message::size
	> instance_array;
public:
	typedef typename call::default_function<
		result_type
	>::type default_function;

	object()
	:
		instances_()
	{
		sge::mpl::for_each<
			Messages
		>(
			make_instance<
				Callee,
				instance_array
			>(
				instances_
			)
		);
	}

	result_type
	operator()(
		base const &message_,
		Callee &callee_,
		default_function const &default_function_
	) const
	{
		return 
			instances_.is_null(
				message_.type()
			)
			?	
				default_function_(
					message_
				)
			:
				instances_[	
					message_.type()
				].call(
					callee_,
					message_
				);
	}
private:
	instance_array instances_;
};

}
}
}

#endif
