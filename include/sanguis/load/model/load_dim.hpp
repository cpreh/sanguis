#ifndef SANGUIS_LOAD_MODEL_LOAD_DIM_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_LOAD_DIM_HPP_INCLUDED

#include <sanguis/load/model/cell_size_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::cell_size const
load_dim(
	sge::parse::json::object const &
);

}
}
}

#endif
