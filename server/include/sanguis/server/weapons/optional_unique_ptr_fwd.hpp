#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::server::weapons
{

using
optional_unique_ptr
=
fcppt::optional::object<
	sanguis::server::weapons::unique_ptr
>;

}

#endif
