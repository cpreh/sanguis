#ifndef SANGUIS_SERVER_ENTITIES_WITH_HEALTH_REF_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_HEALTH_REF_HPP_INCLUDED

#include <sanguis/server/entities/with_health_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::server::entities
{

using
with_health_ref
=
fcppt::reference<
	sanguis::server::entities::with_health
>;

}

#endif
