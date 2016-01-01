#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/optional_info.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/maybe.hpp>


sanguis::client::perk::compare::compare(
	sanguis::perk_type const _type
)
:
	type_(
		_type
	)
{
}

bool
sanguis::client::perk::compare::operator()(
	sanguis::client::perk::tree const &_tree
) const
{
	return
		fcppt::optional::maybe(
			_tree.value(),
			fcppt::const_(
				false
			),
			[
				this
			](
				sanguis::client::perk::info const &_info
			)
			{
				return
					_info.perk_type()
					==
					type_;
			}
		);
}
