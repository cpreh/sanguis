#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_HPP_INCLUDED

#include "context_fwd.hpp"
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
struct dispatcher_register
{
	FCPPT_NONCOPYABLE(
		dispatcher_register
	);
public:
	explicit dispatcher_register(
		serialization::context &
	);
};

}
}
}

#endif
