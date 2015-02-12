#include <sanguis/collision/aux_/world/body_ghost_group_relation.hpp>
#include <sanguis/collision/aux_/world/body_group_container.hpp>
#include <sanguis/collision/aux_/world/body_groups_for_ghost_group.hpp>
#include <sanguis/collision/aux_/world/make_groups.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	sanguis::collision::world::ghost_group Group
>
using
ghost_body_groups_static
=
typename
boost::mpl::fold<
	sanguis::collision::aux_::world::body_ghost_group_relation,
	boost::mpl::vector0<>,
	boost::mpl::if_<
		std::is_same<
			std::integral_constant<
				sanguis::collision::world::ghost_group,
				Group
			>,
			boost::mpl::second<
				boost::mpl::_2
			>
		>,
		boost::mpl::push_back<
			boost::mpl::_1,
			boost::mpl::first<
				boost::mpl::_2
			>
		>,
		boost::mpl::_1
	>
>::type;

auto const groups(
	sanguis::collision::aux_::world::make_groups<
		sanguis::collision::world::ghost_group,
		sanguis::collision::world::body_group,
		ghost_body_groups_static
	>::make()
);

}

sanguis::collision::aux_::world::body_group_container const &
sanguis::collision::aux_::world::body_groups_for_ghost_group(
	sanguis::collision::world::ghost_group const _group
)
{
	return
		groups[
			_group
		];
}
