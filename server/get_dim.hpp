#ifndef SANGUIS_SERVER_GET_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_GET_DIM_HPP_INCLUDED

#include "../messages/types.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace server
{

messages::dim_type get_dim(
	sge::string const &model,
	sge::string const &part);

}
}

#endif
