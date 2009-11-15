#ifndef SANGUIS_MESSAGES_CALLER_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALLER_HPP_INCLUDED

#include "default_function.hpp"
#include "result.hpp"
#include "dispatcher_base.hpp"
#include "make_instance.hpp"
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/size.hpp>

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
	SGE_NONCOPYABLE(caller)

	typedef typename Callee::result_type result_type;

	typedef typename call::default_function<
		result_type
	>::type default_function;

	typedef dispatcher_base<
		Callee
	> dispatcher_base;

	typedef boost::ptr_array<
		boost::mpl::size<
			Messages
		>::value,
		dispatcher_base
	> instance_array;
public:
	explicit object(
		default_function const &default_function_
	)
	:
		default_function_(default_function_)
		instances_()
	{
		boost::mpl::for_each<
			Messages
		>(
			make_instance<
				dispatcher_base	
			>(
				instances_
			)
		);
	}

	result_type
	call(
		Callee &callee_,
		base const &message_
	)
	{
		return 
			instances_.is_null(
				message_->type()
			)
			?	
				default_function_(
					messages_
				)
			:
				instances_[	
					message_->type()
				].call(
					callee_,
					message_
				);
	}
private:
	default_function const default_function_;
	instance_array instances_;
};

}
}
}

#endif
