#ifndef SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED

#include <sanguis/client/perk/tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef
std::pair<
	sanguis::client::perk::tree::const_iterator,
	sanguis::client::perk::tree::const_iterator
>
const_tree_range;

}
}
}

#endif
