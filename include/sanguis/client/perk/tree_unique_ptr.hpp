#ifndef SANGUIS_CLIENT_PERK_TREE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/perk/tree.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef fcppt::unique_ptr<
	perk::tree
> tree_unique_ptr;

}
}
}

#endif
