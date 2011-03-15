#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_HPP_INCLUDED

#include "reader_fwd.hpp"
#include "dispatcher_base.hpp"
#include "../auto_ptr.hpp"

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename T
>
struct dispatcher
:
	dispatcher_base
{
	auto_ptr
	on_dispatch(
		reader const &
	) const;
};

}
}
}

#endif
