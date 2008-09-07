#ifndef SANGUIS_SERVER_GET_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_GET_DIM_HPP_INCLUDED

#include "types.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace server
{

dim_type const
get_dim(
	sge::string const &model,
	sge::string const &part);

dim_type const
default_dim(
	sge::string const &model);

}
}

#endif
