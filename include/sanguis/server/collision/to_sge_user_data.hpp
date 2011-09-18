#ifndef SANGUIS_SERVER_COLLISION_TO_SGE_USER_DATA_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_SGE_USER_DATA_HPP_INCLUDED

#include <sanguis/server/collision/user_data_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/any.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

boost::any const
to_sge_user_data(
	collision::user_data const &
);

}
}
}

#endif
