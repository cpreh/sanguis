#ifndef SANGUIS_SERVER_DAMAGE_BASIC_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/server/damage/type_fwd.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

template<
	typename Unit
>
using
basic_array
=
fcppt::container::enum_array<
	sanguis::server::damage::type,
	Unit
>;

}
}
}

#endif
