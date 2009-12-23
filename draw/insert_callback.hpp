#ifndef SANGUIS_DRAW_INSERT_CALLBACK_HPP_INCLUDED
#define SANGUIS_DRAW_INSERT_CALLBACK_HPP_INCLUDED

#include "entity_auto_ptr.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace draw
{

typedef fcppt::function::object<
	void (
		entity_auto_ptr)
> insert_callback;

}
}

#endif
