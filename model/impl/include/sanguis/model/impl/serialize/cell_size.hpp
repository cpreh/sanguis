#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_CELL_SIZE_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_CELL_SIZE_HPP_INCLUDED

#include <sanguis/model/cell_size_fwd.hpp>
#include <sge/parse/json/member.hpp>

namespace sanguis::model::impl::serialize
{

sge::parse::json::member cell_size(sanguis::model::cell_size const &);

}

#endif
