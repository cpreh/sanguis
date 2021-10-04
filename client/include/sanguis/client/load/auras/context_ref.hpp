#ifndef SANGUIS_CLIENT_LOAD_AURAS_CONTEXT_REF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_AURAS_CONTEXT_REF_HPP_INCLUDED

#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::load::auras
{

using
context_ref
=
fcppt::reference<
	sanguis::client::load::auras::context
>;

}

#endif
