#ifndef SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_HPP_INCLUDED

#include <sanguis/server/damage/type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis::server::damage
{

fcppt::string
type_to_string(
	sanguis::server::damage::type
);

}

#endif
