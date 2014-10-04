#ifndef SANGUIS_COLLISION_AUX__WORLD_MAKE_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_MAKE_GROUPS_HPP_INCLUDED

#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/algorithm/enum_array_fold_static.hpp>
#include <fcppt/container/enum_array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <array>
#include <cstddef>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
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
			std::size_t Index
		>
		ResultGroup
		operator()() const
		{
			return
				boost::mpl::at_c<
					GroupsStatic<
						Group
					>,
					Index
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
			IndexedGroup Group
		>
		result_type
		operator()() const
		{
			groups_array<
				Group
			> const array(
				fcppt::algorithm::array_fold_static<
					groups_array<
						Group
					>
				>(
					make_group<
						Group
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
	fcppt::container::enum_array<
		IndexedGroup,
		result_container
	>
	group_container_array;

	static
	group_container_array
	make()
	{
		return
			fcppt::algorithm::enum_array_fold_static<
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
