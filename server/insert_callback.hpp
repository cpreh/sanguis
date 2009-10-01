#ifndef SANGUIS_SERVER_INSERT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_INSERT_CALLBACK_HPP_INCLUDED

#include "entities/auto_ptr.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	entities::entity & (entities::auto_ptr)
> insert_callback;

}
}

#endif
