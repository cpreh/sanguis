#ifndef SANGUIS_SERVER_ENTITIES_COMBINE_TRANSFER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_COMBINE_TRANSFER_HPP_INCLUDED

#include <sanguis/server/entities/transfer_result_fwd.hpp>


namespace sanguis::server::entities
{

sanguis::server::entities::transfer_result
combine_transfer(
	sanguis::server::entities::transfer_result &&,
	sanguis::server::entities::transfer_result &&
);

}

#endif
