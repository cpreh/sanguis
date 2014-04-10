#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/find_info_any.hpp>
#include <sanguis/client/perk/tree.hpp>


sanguis::client::perk::tree &
sanguis::client::perk::find_info(
	sanguis::perk_type const _type,
	sanguis::client::perk::tree &_tree
)
{
	return
		sanguis::client::perk::find_info_any<
			sanguis::client::perk::tree
		>(
			_type,
			_tree
		);
}
