#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_OBJECT_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_OBJECT_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis::model::impl::deserialize
{

sanguis::model::object object(sge::parse::json::object const &);

}

#endif
