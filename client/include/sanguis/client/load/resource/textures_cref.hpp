#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURES_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURES_CREF_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::load::resource
{

using
textures_cref
=
fcppt::reference<
	sanguis::client::load::resource::textures const
>;

}

#endif
