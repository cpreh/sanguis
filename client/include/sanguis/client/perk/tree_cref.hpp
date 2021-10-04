#ifndef SANGUIS_CLIENT_PERK_TREE_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_CREF_HPP_INCLUDED

#include <sanguis/client/perk/tree_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::perk
{

using
tree_cref
=
fcppt::reference<
	sanguis::client::perk::tree const
>;

}

#endif
