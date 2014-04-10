#ifndef SANGUIS_SERVER_COLLISION_OPTIONAL_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_OPTIONAL_RESULT_FWD_HPP_INCLUDED

#include <sanguis/server/collision/result_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

typedef
fcppt::optional<
	sanguis::server::collision::result
> optional_result;

}
}
}

#endif
