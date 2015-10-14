#ifndef SANGUIS_CLIENT_PERK_CATEGORY_EQUAL_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CATEGORY_EQUAL_RANGE_HPP_INCLUDED

#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/tree.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

sanguis::client::perk::const_tree_range
category_equal_range(
	sanguis::client::perk::tree::const_iterator,
	sanguis::client::perk::tree::const_iterator
);

}
}
}

#endif
