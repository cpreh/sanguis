#ifndef SANGUIS_SERVER_EXP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_EXP_CALLBACK_HPP_INCLUDED

#include "exp_type.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (exp_type)
> exp_callback;

}
}

#endif
