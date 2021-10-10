#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_OBJECT_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_OBJECT_HPP_INCLUDED

#include <sanguis/model/object_fwd.hpp>
#include <sge/parse/json/object.hpp>

namespace sanguis::model::impl::serialize
{

sge::parse::json::object object(sanguis::model::object const &);

}

#endif
