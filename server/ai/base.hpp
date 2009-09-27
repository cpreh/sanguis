#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../../time_type.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

class base {
	SGE_NONCOPYABLE(base)
protected:
	base();
public:
	virtual void
	update(
		time_type
	) = 0;
	
	virtual ~base();
};

}
}
}

#endif
