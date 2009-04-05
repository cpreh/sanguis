#ifndef SANGUIS_MESSAGES_SERIALIZATION_CONTEXT_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "dispatch_map.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

struct context {
	SGE_NONCOPYABLE(context)
public:
	context();

	~context();

	dispatch_map const &
	handlers() const;
private:
	dispatch_map handlers_;

	template<
		typename T
	> friend class dispatcher_register;
};

}
}
}

#endif
