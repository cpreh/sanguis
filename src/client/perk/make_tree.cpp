#include "make_tree.hpp"
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <boost/foreach.hpp>

#include <iostream>

sanguis::client::perk::tree const
sanguis::client::perk::make_tree(
	messages::perk_tree_node_list const &_list
)
{
	perk::tree ret(
		sanguis::perk_type::size
	);

	BOOST_FOREACH(
		messages::perk_tree_node_list::const_reference cur,
		_list
	)
	{
		std::cout <<
			static_cast<unsigned>(cur.get<messages::roles::perk_label>())
			<< '\n';
	
		BOOST_FOREACH(
			messages::types::enum_vector::const_reference child,
			cur.get<messages::roles::perk_children>()
		)
			std::cout << '\t'
				<< static_cast<unsigned>(child)
				<< '\n';
	}

	return ret;
}
