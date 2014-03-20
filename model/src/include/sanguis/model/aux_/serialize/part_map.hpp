#ifndef SANGUIS_MODEL_AUX__SERIALIZE_PART_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_PART_MAP_HPP_INCLUDED

#include <sanguis/model/part_map.hpp>
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
part_map(
	sanguis::model::part_map const &
);

}
}
}
}

#endif
