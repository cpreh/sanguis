#ifndef SANGUIS_SERVER_PERKS_TREE_FIND_NODE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_FIND_NODE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/type_from_container.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::perks::tree
{

template<
	typename Container
>
fcppt::optional::reference<
	sanguis::server::perks::tree::type_from_container<
		Container
	>
>
find_node(
	Container &_container,
	sanguis::perk_type const _perk_type
)
{
	using
	tree_type
	=
	sanguis::server::perks::tree::type_from_container<
		Container
	>;

	using
	result_type
	=
	fcppt::optional::reference<
		tree_type
	>;

	for(
		tree_type &element
		:
		_container
	)
	{
		using
		traversal
		=
		fcppt::container::tree::pre_order<
			tree_type
		>;

		traversal trav(
			element
		);

		// TODO(philipp): find_by?
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
		{
			return
				result_type(
					fcppt::make_ref(
						*it
					)
				);
		}
	}

	return
		result_type();
}

}

#endif
