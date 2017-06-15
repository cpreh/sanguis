#ifndef SANGUIS_COLLISION_IMPL_WORLD_MAKE_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_MAKE_GROUPS_HPP_INCLUDED

#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <array>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{

template<
	typename IndexedGroup,
	typename ResultGroup,
	template<
		IndexedGroup
	> class GroupsStatic
>
struct make_groups
{
private:
	template<
		IndexedGroup Group
	>
	using
	groups_array
	=
	std::array<
		ResultGroup,
		boost::mpl::size<
			GroupsStatic<
				Group
			>
		>::value
	>;

	template<
		IndexedGroup Group
	>
	struct make_group
	{
		template<
			typename Index
		>
		ResultGroup
		operator()(
			Index
		) const
		{
			return
				boost::mpl::at_c<
					GroupsStatic<
						Group
					>,
					Index::value
				>::type::value;
		}
	};

	typedef
	std::vector<
		ResultGroup
	>
	result_container;

	struct make_container
	{
		typedef
		result_container
		result_type;

		template<
			typename Group
		>
		result_type
		operator()(
			Group
		) const
		{
			groups_array<
				Group::value
			> const array(
				fcppt::algorithm::array_init<
					groups_array<
						Group::value
					>
				>(
					make_group<
						Group::value
					>()
				)
			);

			return
				result_container(
					array.begin(),
					array.end()
				);
		}
	};
public:
	typedef
	fcppt::enum_::array<
		IndexedGroup,
		result_container
	>
	group_container_array;

	static
	group_container_array
	make()
	{
		return
			fcppt::enum_::array_init<
				group_container_array
			>(
				make_container()
			);
	}
};

}
}
}
}

#endif
