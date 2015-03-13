#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_TRANSFER_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_TRANSFER_RESULT_FWD_HPP_INCLUDED

#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::optional<
	sanguis::server::entities::transfer_result
>
optional_transfer_result;

}
}
}

#endif
