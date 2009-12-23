#ifndef SANGUIS_CLIENT_CURSOR_OBJECT_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_OBJECT_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <fcppt/shared_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace cursor
{
typedef sge::shared_ptr<object> object_ptr;
}
}
}


#endif
