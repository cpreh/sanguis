#include "equal.hpp"
#include "status.hpp"
#include <fcppt/container/tree/object_impl.hpp>

sanguis::server::perks::tree::equal::equal(
	sanguis::perk_type::type const _type
)
:
	type_(_type)
{
}

bool
sanguis::server::perks::tree::equal::operator()(
	tree::object const &_tree
) const
{
	return _tree.value().type() == type_;
}
