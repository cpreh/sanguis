#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_IMAGE_NAME_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_IMAGE_NAME_HPP_INCLUDED

#include <sanguis/model/optional_image_name.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis::model::impl::deserialize
{

sanguis::model::optional_image_name image_name(sge::parse::json::object const &);

}

#endif
