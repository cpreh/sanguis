#ifndef SANGUIS_CLIENT_PERK_STATE_REF_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_STATE_REF_HPP_INCLUDED

#include <sanguis/client/perk/state_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::perk
{

using
state_ref
=
fcppt::reference<
	sanguis::client::perk::state
>;

}

#endif
