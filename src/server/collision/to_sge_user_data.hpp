#ifndef SANGUIS_SERVER_COLLISION_TO_SGE_USER_DATA_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_SGE_USER_DATA_HPP_INCLUDED

#include "user_data_fwd.hpp"
#include <boost/any.hpp>

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
