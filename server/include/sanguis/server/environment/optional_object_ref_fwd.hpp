#ifndef SANGUIS_SERVER_ENVIRONMENT_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED

#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sanguis::server::environment
{

using
optional_object_ref
=
fcppt::optional::reference<
	sanguis::server::environment::object
>;

}

#endif
