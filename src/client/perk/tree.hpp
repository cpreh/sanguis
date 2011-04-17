#ifndef SANGUIS_CLIENT_PERK_TREE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_HPP_INCLUDED

#include "info_fwd.hpp"
#include <fcppt/container/tree/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef fcppt::container::tree::object<
	perk::info
> tree;

}
}
}

#endif
