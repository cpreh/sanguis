#ifndef SANGUIS_SERVER_COLLISION_FROM_SGE_USER_DATA_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_FROM_SGE_USER_DATA_HPP_INCLUDED

#include "user_data_fwd.hpp"
#include <boost/any.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

collision::user_data const
from_sge_user_data(
	boost::any const &
);

}
}
}

#endif
