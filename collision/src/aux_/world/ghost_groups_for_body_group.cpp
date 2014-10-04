#include <sanguis/collision/aux_/world/body_ghost_group_relation.hpp>
#include <sanguis/collision/aux_/world/ghost_group_container.hpp>
#include <sanguis/collision/aux_/world/ghost_groups_for_body_group.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/algorithm/enum_array_fold_static.hpp>
#include <fcppt/container/enum_array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <array>
#include <cstddef>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	sanguis::collision::world::body_group Group
>
using
body_ghost_groups_static
=
typename
boost::mpl::fold<
	sanguis::collision::aux_::world::body_ghost_group_relation,
	boost::mpl::vector0<>,
	boost::mpl::if_<
		std::is_same<
			std::integral_constant<
				sanguis::collision::world::body_group,
				Group
			>,
			boost::mpl::first<
				boost::mpl::_2
			>
		>,
		boost::mpl::push_back<
			boost::mpl::_1,
			boost::mpl::second<
				boost::mpl::_2
			>
		>,
		boost::mpl::_1
	>
>::type;

template<
	sanguis::collision::world::body_group Group
>
using
body_ghost_groups_array
=
std::array<
	sanguis::collision::world::ghost_group,
	boost::mpl::size<
		body_ghost_groups_static<
			Group
		>
	>::value
>;

template<
	sanguis::collision::world::body_group Group
>
struct make_body_ghost_group
{
	template<
		std::size_t Index
	>
	sanguis::collision::world::ghost_group
	operator()() const
	{
		return
			boost::mpl::at_c<
				body_ghost_groups_static<
					Group
				>,
				Index
			>::type::value;
	}
};

struct make_container
{
	typedef
	sanguis::collision::aux_::world::ghost_group_container
	result_type;

	template<
		sanguis::collision::world::body_group Group
	>
	result_type
	operator()() const
	{
		body_ghost_groups_array<
			Group
		> const array(
			fcppt::algorithm::array_fold_static<
				body_ghost_groups_array<
					Group
				>
			>(
				make_body_ghost_group<
					Group
				>()
			)
		);

		return
			sanguis::collision::aux_::world::ghost_group_container(
				array.begin(),
				array.end()
			);
	}
};

typedef
fcppt::container::enum_array<
	sanguis::collision::world::body_group,
	sanguis::collision::aux_::world::ghost_group_container
>
body_group_array;

body_group_array const groups(
	fcppt::algorithm::enum_array_fold_static<
		body_group_array
	>(
		make_container()
	)
);

}

sanguis::collision::aux_::world::ghost_group_container const &
sanguis::collision::aux_::world::ghost_groups_for_body_group(
	sanguis::collision::world::body_group const _group
)
{
	return
		groups[
			_group
		];
}
