#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_IMAGE_NAME_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_IMAGE_NAME_HPP_INCLUDED

#include <sanguis/model/optional_image_name_fwd.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sanguis::model::impl::serialize
{

fcppt::optional::object<sge::parse::json::member>
image_name(sanguis::model::optional_image_name const &);

}

#endif
