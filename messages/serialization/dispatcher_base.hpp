#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_BASE_HPP_INCLUDED

#include "../auto_ptr.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

class reader;

struct dispatcher_base {
	SGE_NONCOPYABLE(dispatcher_base)
protected:
	dispatcher_base();
public:
	virtual auto_ptr
	on_dispatch(
		reader const &) const = 0;

	virtual ~dispatch_base();
};

}
}
}

#endif
