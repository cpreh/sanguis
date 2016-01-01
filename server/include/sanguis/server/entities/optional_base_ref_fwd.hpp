#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_BASE_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_BASE_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::optional::object<
	sanguis::server::entities::base &
>
optional_base_ref;

}
}
}

#endif
