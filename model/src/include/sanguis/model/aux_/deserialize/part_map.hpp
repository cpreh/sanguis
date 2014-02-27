#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_PART_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_PART_MAP_HPP_INCLUDED

#include <sanguis/model/part_map.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::part_map
part_map(
	sanguis::model::aux_::deserialize::parameters const &,
	sge::parse::json::object const &
);

}
}
}
}

#endif
