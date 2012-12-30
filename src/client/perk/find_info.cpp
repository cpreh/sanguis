#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>


sanguis::client::perk::tree const &
sanguis::client::perk::find_info(
	sanguis::perk_type const _type,
	sanguis::client::perk::tree const &_tree
)
{
	typedef fcppt::container::tree::pre_order<
		perk::tree const
	> traversal;

	traversal trav(
		_tree
	);

	return
		*fcppt::algorithm::find_if_exn(
			trav.begin(),
			trav.end(),
			sanguis::client::perk::compare(
				_type
			)
		);
}
