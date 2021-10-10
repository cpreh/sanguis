#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_BODY_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_BODY_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace sanguis::server::entities
{

using optional_with_body_ref = fcppt::optional::reference<sanguis::server::entities::with_body>;

}

#endif
