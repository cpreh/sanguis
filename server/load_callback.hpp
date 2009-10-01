#ifndef SANGUIS_SERVER_LOAD_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_LOAD_CALLBACK_HPP_INCLUDED

#include "../load/context_fwd.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	load::context const &()
> load_callback;

}
}

#endif
