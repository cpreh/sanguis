#ifndef SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED

#include <sanguis/client/perk/tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef
boost::iterator_range<
	sanguis::client::perk::tree::const_iterator
>
const_tree_range;

}
}
}

#endif
