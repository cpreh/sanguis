#ifndef SANGUIS_MODEL_AUX__SERIALIZE_OBJECT_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_OBJECT_HPP_INCLUDED

#include <sanguis/model/object_fwd.hpp>
#include <sge/parse/json/object.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace serialize
{

sge::parse::json::object
object(
	sanguis::model::object const &
);

}
}
}
}

#endif
