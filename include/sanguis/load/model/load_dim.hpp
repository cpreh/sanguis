#ifndef SANGUIS_LOAD_MODEL_LOAD_DIM_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_LOAD_DIM_HPP_INCLUDED

#include <sge/parse/json/member_map.hpp>
#include <sge/renderer/dim2.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

sge::renderer::dim2 const
load_dim(
	sge::parse::json::member_map const &
);

}
}
}

#endif
