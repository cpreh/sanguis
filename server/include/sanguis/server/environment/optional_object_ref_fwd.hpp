#ifndef SANGUIS_SERVER_ENVIRONMENT_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED

#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace environment
{

typedef
fcppt::optional::reference<
	sanguis::server::environment::object
>
optional_object_ref;

}
}
}

#endif
