#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_CELL_SIZE_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_CELL_SIZE_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::cell_size const
cell_size(
	sge::parse::json::object const &
);

}
}
}
}

#endif
