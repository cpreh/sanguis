#ifndef SANGUIS_SERVER_ENTITIES_WITH_ID_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_ID_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/with_id_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::server::entities
{

using with_id_unique_ptr = fcppt::unique_ptr<sanguis::server::entities::with_id>;

}

#endif
