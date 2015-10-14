#ifndef SANGUIS_SERVER_DAMAGE_UNMODIFIED_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_UNMODIFIED_HPP_INCLUDED

#include <sanguis/server/damage/array_fwd.hpp>
#include <sanguis/server/damage/modified_array.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

sanguis::server::damage::modified_array
unmodified(
	sanguis::server::damage::array const &
);

}
}
}

#endif
