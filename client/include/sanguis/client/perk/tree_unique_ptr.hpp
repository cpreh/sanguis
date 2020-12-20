#ifndef SANGUIS_CLIENT_PERK_TREE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/perk/tree_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

using
tree_unique_ptr
=
fcppt::unique_ptr<
	sanguis::client::perk::tree
>;

}
}
}

#endif
