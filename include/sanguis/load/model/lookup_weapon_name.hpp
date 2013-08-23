#ifndef SANGUIS_LOAD_MODEL_LOOKUP_WEAPON_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_LOOKUP_WEAPON_NAME_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::optional_primary_weapon_type const
lookup_weapon_name(
	fcppt::string const &
);

}
}
}

#endif
