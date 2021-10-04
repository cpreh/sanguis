#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_PART_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_PART_HPP_INCLUDED

#include <sanguis/model/part.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis::model::impl::deserialize
{

sanguis::model::part
part(
	sge::parse::json::object const &
);

}

#endif
