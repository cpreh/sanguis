#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/load/model/part_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::load::model
{

using part_unique_ptr = fcppt::unique_ptr<sanguis::client::load::model::part>;

}

#endif
