#include "choose.hpp"
#include "equal.hpp"
#include "status.hpp"
#include "../../../exception.hpp"
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/text.hpp>

void
sanguis::server::perks::tree::choose(
	tree::object &_tree,
	sanguis::perk_type::type const _perk
)
{
	typedef 
	fcppt::container::tree::pre_order<
		tree::object
	> traversal;
	
	traversal trav(
		_tree
	);
	
	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			tree::equal(	
				_perk
			)
		)
	);
	
	if(
		it == trav.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Perk not found in the tree!")
		);
	
	(*it).value().choose();
}
