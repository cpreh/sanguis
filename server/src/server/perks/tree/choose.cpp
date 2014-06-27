#include <sanguis/exception.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/choose.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/find_node.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/text.hpp>


void
sanguis::server::perks::tree::choose(
	sanguis::server::perks::tree::container &_tree,
	sanguis::perk_type const _perk_type
)
{
	sanguis::server::perks::tree::object::optional_ref const node(
		sanguis::server::perks::tree::find_node(
			_tree,
			_perk_type
		)
	);

	if(
		!node
	)
		throw sanguis::exception(
			FCPPT_TEXT("Perk not found in the tree!")
		);

	node->value().choose();
}
