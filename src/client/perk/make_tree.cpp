#include "make_tree.hpp"
#include "info.hpp"
#include "max_level.hpp"
#include "required_parent_level.hpp"
#include "required_player_level.hpp"
#include "../../cast_enum.hpp"
#include "../../perk_type.hpp"
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/foreach.hpp>

namespace
{

sanguis::client::perk::info const
make_info(
	sanguis::messages::perk_tree_node const &
);

class compare_perk
{
	FCPPT_NONASSIGNABLE(
		compare_perk
	);
public:
	explicit compare_perk(
		sanguis::perk_type::type
	);

	bool
	operator()(
		sanguis::client::perk::tree const &
	) const;
private:
	sanguis::perk_type::type const type_;
};

}

sanguis::client::perk::tree_unique_ptr
sanguis::client::perk::make_tree(
	messages::perk_tree_node_list const &_list
)
{
	// this code highly depends on the order in which the server serializes the tree
	
	FCPPT_ASSERT(
		!_list.empty()
	);

	// start with the dummy head, the server will always send one
	perk::tree_unique_ptr ret(
		fcppt::make_unique_ptr<
			perk::tree
		>(
			::make_info(
				_list.front()
			)
		)
	);

	BOOST_FOREACH(
		messages::perk_tree_node_list::const_reference cur,
		_list
	)
	{
		typedef fcppt::container::tree::pre_order<
			perk::tree
		> traversal;

		traversal trav(
			*ret
		);

		traversal::iterator const pos(
			fcppt::algorithm::find_if_exn(
				trav.begin(),
				trav.end(),
				::compare_perk(
					SANGUIS_CAST_ENUM(
						perk_type,
						cur.get<
							messages::roles::perk_label
						>()
					)
				)
			)
		);

		pos->value(
			::make_info(
				cur
			)
		);

		BOOST_FOREACH(
			messages::types::enum_vector::const_reference child,
			cur.get<messages::roles::perk_children>()
		)
			pos->push_back(
				perk::info(
					SANGUIS_CAST_ENUM(
						perk_type,
						child	
					)
				)
			);
	}

	return
		move(
			ret
		);
}

namespace
{

sanguis::client::perk::info const
make_info(
	sanguis::messages::perk_tree_node const &_node
)
{
	return
		sanguis::client::perk::info(
			SANGUIS_CAST_ENUM(
				sanguis::perk_type,
				_node.get<
					sanguis::messages::roles::perk_label
				>()
			),
			sanguis::client::perk::required_parent_level(
				_node.get<
					sanguis::messages::roles::required_perk_parent_level
				>()
			),
			sanguis::client::perk::required_player_level(
				_node.get<
					sanguis::messages::roles::required_perk_player_level
				>()
			),
			sanguis::client::perk::max_level(
				_node.get<
					sanguis::messages::roles::max_perk_level
				>()
			)
		);
}

compare_perk::compare_perk(
	sanguis::perk_type::type const _type
)
:
	type_(_type)
{
}

bool
compare_perk::operator()(
	sanguis::client::perk::tree const &_tree
) const
{
	return _tree.value().type() == type_;
}

}
