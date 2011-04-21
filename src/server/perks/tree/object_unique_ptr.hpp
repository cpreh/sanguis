#ifndef SANGUIS_SERVER_PERKS_TREE_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include "object.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

typedef fcppt::unique_ptr<
	tree::object
> object_unique_ptr;

}
}
}
}

#endif
