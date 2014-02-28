#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_IMAGE_NAME_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_IMAGE_NAME_HPP_INCLUDED

#include <sanguis/model/optional_image_name.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::optional_image_name
image_name(
	sge::parse::json::object const &
);

}
}
}
}

#endif
