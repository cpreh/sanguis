#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_PART_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_PART_HPP_INCLUDED

#include <sanguis/model/part_fwd.hpp>
#include <sge/parse/json/object.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{
namespace serialize
{

sge::parse::json::object
part(
	sanguis::model::part const &
);

}
}
}
}

#endif
