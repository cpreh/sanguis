#ifndef SANGUIS_MESSAGES_CALL_OBJECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_OBJECT_HPP_INCLUDED

#include "default_function.hpp"
#include "dispatcher_base.hpp"
#include "make_instance.hpp"
#include "../base_fwd.hpp"
#include "../types/message.hpp"
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/noncopyable.hpp>
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
class object
{
	FCPPT_NONCOPYABLE(
		object
	);

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
		fcppt::mpl::for_each<
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
		base const &_message,
		Callee &_callee,
		default_function const &_default_function
	) const
	{
		return 
			instances_.is_null(
				_message.type()
			)
			?	
				_default_function(
					_message
				)
			:
				instances_[
					_message.type()
				].call(
					_callee,
					_message
				);
	}
private:
	instance_array instances_;
};

}
}
}

#endif
