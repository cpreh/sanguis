#ifndef SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED

#include "pos_fn.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{

typedef sge::function::object<
	pos_fn
> pos_callback;

}
}
}

#endif // SANGUIS_CLIENT_CURSOR_POS_CALLBACK_HPP_INCLUDED
