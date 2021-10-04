#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_REF_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_REF_HPP_INCLUDED

#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::server::environment
{

using
object_ref
=
fcppt::reference<
	sanguis::server::environment::object
>;

}

#endif
