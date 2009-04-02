#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_HPP_INCLUDED

#include "context_fwd.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename T
>
struct dispatcher_register {
	SGE_NONCOPYABLE(dispatcher_register)
public:
	explicit dispatcher_register(
		context &ctx);
};

}
}
}

#endif
