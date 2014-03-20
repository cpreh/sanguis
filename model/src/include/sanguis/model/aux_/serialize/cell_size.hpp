#ifndef SANGUIS_MODEL_AUX__SERIALIZE_CELL_SIZE_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_CELL_SIZE_HPP_INCLUDED

#include <sanguis/model/cell_size_fwd.hpp>
#include <sge/parse/json/member.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace serialize
{

sge::parse::json::member
cell_size(
	sanguis::model::cell_size
);

}
}
}
}

#endif
