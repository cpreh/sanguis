#ifndef SANGUIS_DRAW_INSERT_CALLBACK_HPP_INCLUDED
#define SANGUIS_DRAW_INSERT_CALLBACK_HPP_INCLUDED

#include "entity_auto_ptr.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace draw
{

typedef boost::function<
	void (
		entity_auto_ptr)
> insert_callback;

}
}

#endif
