#ifndef SANGUIS_MESSAGES_CALL_MAKE_INSTANCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_MAKE_INSTANCE_HPP_INCLUDED

#include <sanguis/messages/call/dispatcher.hpp>
#include <sanguis/messages/message_id.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

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
class make_instance
{
	FCPPT_NONASSIGNABLE(
		make_instance
	);
public:
	explicit make_instance(
		InstanceArray &_instances
	)
	:
		instances_(_instances)
	{
	}

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

		std::auto_ptr<
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
