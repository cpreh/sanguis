#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <fcppt/container/tree/object_impl.hpp>

sanguis::client::perk::compare::compare(
	sanguis::perk_type::type const _type
)
:
	type_(_type)
{
}

bool
sanguis::client::perk::compare::operator()(
	sanguis::client::perk::tree const &_tree
) const
{
	return _tree.value().type() == type_;
}
