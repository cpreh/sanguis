#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_PART_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_PART_MAP_HPP_INCLUDED

#include <sanguis/model/part_map.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis::model::impl::deserialize
{

sanguis::model::part_map part_map(sge::parse::json::object const &);

}

#endif
