#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_TRANSFER_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_TRANSFER_RESULT_FWD_HPP_INCLUDED

#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::server::entities
{

using
optional_transfer_result
=
fcppt::optional::object<
	sanguis::server::entities::transfer_result
>;

}

#endif
