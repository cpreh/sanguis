#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_CELL_SIZE_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_CELL_SIZE_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis::model::impl::deserialize
{

sanguis::model::cell_size cell_size(sge::parse::json::object const &);

}

#endif
