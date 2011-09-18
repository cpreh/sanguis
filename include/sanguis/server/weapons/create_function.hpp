#ifndef SANGUIS_SERVER_WEAPONS_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

// TODO: can we make this return an auto_ptr?
typedef fcppt::function::object<
	weapon *()
> create_function;

}
}
}

#endif
