#ifndef SANGUIS_CLIENT_LOAD_TILES_CONTEXT_REF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_CONTEXT_REF_HPP_INCLUDED

#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::load::tiles
{

using
context_ref
=
fcppt::reference<
	sanguis::client::load::tiles::context
>;

}

#endif
