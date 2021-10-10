#ifndef SANGUIS_CLIENT_LOAD_MODEL_OBJECT_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_OBJECT_CREF_HPP_INCLUDED

#include <sanguis/client/load/model/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::client::load::model
{

using object_cref = fcppt::reference<sanguis::client::load::model::object const>;

}

#endif
