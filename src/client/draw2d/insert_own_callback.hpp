#ifndef SANGUIS_CLIENT_DRAW2D_INSERT_OWN_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_INSERT_OWN_CALLBACK_HPP_INCLUDED

#include "entities/own_auto_ptr.hpp"
#include "entities/own.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef fcppt::function::object<
	entities::own &(
		entities::own_auto_ptr
	)
> insert_own_callback;

}
}
}

#endif
