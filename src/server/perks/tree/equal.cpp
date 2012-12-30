#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/equal.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>


sanguis::server::perks::tree::equal::equal(
	sanguis::perk_type const _type
)
:
	type_(
		_type
	)
{
}

bool
sanguis::server::perks::tree::equal::operator()(
	sanguis::server::perks::tree::object const &_tree
) const
{
	return _tree.value().type() == type_;
}
