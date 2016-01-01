#ifndef SANGUIS_SERVER_WEAPONS_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::optional::object<
	sanguis::server::weapons::unique_ptr
>
optional_unique_ptr;

}
}
}

#endif
