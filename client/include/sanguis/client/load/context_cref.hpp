#ifndef SANGUIS_CLIENT_LOAD_CONTEXT_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_CONTEXT_CREF_HPP_INCLUDED

#include <sanguis/client/load/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::load
{

using
context_cref
=
fcppt::reference<
	sanguis::client::load::context const
>;

}

#endif
