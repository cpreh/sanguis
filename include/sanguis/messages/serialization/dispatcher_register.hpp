#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_HPP_INCLUDED

#include <sanguis/messages/serialization/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename T
>
class dispatcher_register
{
	FCPPT_NONCOPYABLE(
		dispatcher_register
	);
public:
	explicit dispatcher_register(
		serialization::context &
	);

	~dispatcher_register();
};

}
}
}

#endif
