#include <sanguis/exception.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/choose.hpp>
#include <sanguis/server/perks/tree/equal.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/tree/pre_order.hpp>


void
sanguis::server::perks::tree::choose(
	sanguis::server::perks::tree::object &_tree,
	sanguis::perk_type const _perk
)
{
	typedef
	fcppt::container::tree::pre_order<
		sanguis::server::perks::tree::object
	> traversal;

	traversal trav(
		_tree
	);

	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			sanguis::server::perks::tree::equal(
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
