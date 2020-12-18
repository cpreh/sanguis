#ifndef SANGUIS_SERVER_DAMAGE_MODIFIED_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_MODIFIED_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/server/damage/basic_array_fwd.hpp>
#include <sanguis/server/damage/modified_unit_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

using
modified_array
=
sanguis::server::damage::basic_array<
	sanguis::server::damage::modified_unit
>;

}
}
}

#endif
