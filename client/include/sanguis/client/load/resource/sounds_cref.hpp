#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_CREF_HPP_INCLUDED

#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::client::load::resource
{

using sounds_cref = fcppt::reference<sanguis::client::load::resource::sounds const>;

}

#endif
