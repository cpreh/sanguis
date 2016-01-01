#ifndef SANGUIS_SERVER_OPTIONAL_MASS_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_OPTIONAL_MASS_FWD_HPP_INCLUDED

#include <sanguis/server/mass_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::optional::object<
	sanguis::server::mass
>
optional_mass;

}
}

#endif
