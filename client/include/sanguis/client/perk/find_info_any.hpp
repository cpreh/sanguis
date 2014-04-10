#ifndef SANGUIS_CLIENT_PERK_FIND_INFO_ANY_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_FIND_INFO_ANY_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/container/tree/pre_order.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

template<
	typename Tree
>
Tree &
find_info_any(
	sanguis::perk_type const _type,
	Tree &_tree
)
{
	typedef
	fcppt::container::tree::pre_order<
		Tree
	>
	traversal;

	traversal trav(
		_tree
	);

	return
		*fcppt::algorithm::find_if_exn(
			trav.begin(),
			trav.end(),
			sanguis::client::perk::compare(
				_type
			)
		);
}

}
}
}

#endif
