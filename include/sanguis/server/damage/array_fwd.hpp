#ifndef SANGUIS_SERVER_DAMAGE_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

typedef
fcppt::container::enum_array<
	sanguis::server::damage::type,
	sanguis::server::damage::unit
>
array;

}
}
}

#endif
