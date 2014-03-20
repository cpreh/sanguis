#ifndef SANGUIS_MODEL_AUX__SERIALIZE_IMAGE_NAME_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_IMAGE_NAME_HPP_INCLUDED

#include <sanguis/model/optional_image_name_fwd.hpp>
#include <sge/parse/json/optional_member.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace serialize
{

sge::parse::json::optional_member
image_name(
	sanguis::model::optional_image_name const &
);

}
}
}
}

#endif
