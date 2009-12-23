#ifndef SANGUIS_CLIENT_CURSOR_VISIBLE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_VISIBLE_CALLBACK_HPP_INCLUDED

#include "visible_fn.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{

typedef fcppt::function::object<
	visible_fn
> visible_callback;

}
}
}

#endif // SANGUIS_CLIENT_CURSOR_VISIBLE_CALLBACK_HPP_INCLUDED
