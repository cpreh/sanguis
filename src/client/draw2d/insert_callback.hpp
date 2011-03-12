#ifndef SANGUIS_CLIENT_DRAW2D_INSERT_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_INSERT_CALLBACK_HPP_INCLUDED

#include "entities/auto_ptr.hpp"
#include "entities/base.hpp"
#include "../../entity_id.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef fcppt::function::object<
	entities::base &(
		entities::auto_ptr,
		entity_id
	)
> insert_callback;

}
}
}

#endif
