#ifndef SANGUIS_SERVER_WEAPONS_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_FUNCTION_HPP_INCLUDED

#include "weapon_fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

// TODO: can we make this return an auto_ptr?
typedef boost::function<
	weapon *()
> create_function;

}
}
}

#endif
