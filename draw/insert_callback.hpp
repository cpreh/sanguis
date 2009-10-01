#ifndef SANGUIS_DRAW_INSERT_CALLBACK_HPP_INCLUDED
#define SANGUIS_DRAW_INSERT_CALLBACK_HPP_INCLUDED

#include "entity_auto_ptr.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace draw
{

typedef sge::function::object<
	void (
		entity_auto_ptr)
> insert_callback;

}
}

#endif
