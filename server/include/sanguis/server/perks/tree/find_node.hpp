#ifndef SANGUIS_SERVER_PERKS_TREE_FIND_NODE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_FIND_NODE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/type_from_container.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

template<
	typename Container
>
fcppt::optional::object<
	sanguis::server::perks::tree::type_from_container<
		Container
	> &
>
find_node(
	Container &_container,
	sanguis::perk_type const _perk_type
)
{
	typedef
	sanguis::server::perks::tree::type_from_container<
		Container
	>
	tree_type;

	typedef
	fcppt::optional::object<
		tree_type &
	>
	result_type;

	for(
		tree_type &element
		:
		_container
	)
	{
		typedef
		fcppt::container::tree::pre_order<
			tree_type
		>
		traversal;

		traversal trav(
			element
		);

		typename
		traversal::iterator const it(
			std::find_if(
				trav.begin(),
				trav.end(),
				[
					_perk_type
				](
					tree_type const &_tree
				)
				{
					return
						_tree.value().type()
						==
						_perk_type;
				}
			)
		);

		if(
			it
			!=
			trav.end()
		)
			return
				result_type(
					*it
				);
	}

	return
		result_type();
}

}
}
}
}

#endif
