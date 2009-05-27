#ifndef SANGUIS_SERVER_GET_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_GET_DIM_HPP_INCLUDED

#include "../load/model/context_fwd.hpp"
#include "dim_type.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace server
{

dim_type const
default_dim(
	load::model::context const &,
	sge::string const &model);

}
}

#endif