#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include "../world/map.hpp"
#include "../../world_id.hpp"
#include "../../messages/auto_ptr.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class context {
	SGE_NONCOPYABLE(context)
public:
	context();
	~context();

	void
	send(
		world_id,
		messages::auto_ptr
	);

private:
	world::map worlds_;
};

}
}
}

#endif
