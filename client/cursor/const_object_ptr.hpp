#ifndef SANGUIS_CLIENT_CURSOR_CONST_OBJECT_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_CONST_OBJECT_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{
typedef sge::shared_ptr<object const> const_object_ptr;
}
}
}


#endif