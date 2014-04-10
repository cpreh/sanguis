#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/find_info_any.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/tree.hpp>


sanguis::client::perk::tree const &
sanguis::client::perk::find_info_const(
	sanguis::perk_type const _type,
	sanguis::client::perk::tree const &_tree
)
{
	return
		sanguis::client::perk::find_info_any<
			sanguis::client::perk::tree const
		>(
			_type,
			_tree
		);
}
