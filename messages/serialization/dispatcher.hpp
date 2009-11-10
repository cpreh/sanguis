#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_HPP_INCLUDED

#include "dispatcher_base.hpp"
#include "../auto_ptr.hpp"

namespace sanguis
{
namespace messages
{
namespace serialization
{

struct reader;

template<
	typename T
>
struct dispatcher : dispatcher_base {
	auto_ptr
	on_dispatch(
		reader const &d
	) const;
};

}
}
}

#endif
