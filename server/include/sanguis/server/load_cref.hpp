#ifndef SANGUIS_SERVER_LOAD_CREF_HPP_INCLUDED
#define SANGUIS_SERVER_LOAD_CREF_HPP_INCLUDED

#include <sanguis/server/load_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::server
{

using
load_cref
=
fcppt::reference<
	sanguis::server::load const
>;

}

#endif
