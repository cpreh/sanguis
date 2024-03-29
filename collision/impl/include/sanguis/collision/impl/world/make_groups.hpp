#ifndef SANGUIS_COLLISION_IMPL_WORLD_MAKE_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_MAKE_GROUPS_HPP_INCLUDED

#include <fcppt/array/init.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/mpl/size_type.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/list/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis::collision::impl::world
{

template <typename IndexedGroup, typename ResultGroup, template <IndexedGroup> class GroupsStatic>
struct make_groups
{
private:
  template <IndexedGroup Group>
  using groups_array =
      fcppt::array::object<ResultGroup, fcppt::mpl::list::size<GroupsStatic<Group>>::value>;

  template <IndexedGroup Group>
  struct make_group
  {
    template <typename Index>
    ResultGroup operator()(Index) const
    {
      return fcppt::mpl::list::at<GroupsStatic<Group>, fcppt::mpl::size_type<Index::value>>::type::value;
    }
  };

  using result_container = std::vector<ResultGroup>;

  struct make_container
  {
    template <typename Group>
    result_container operator()(Group) const
    {
      auto const array(fcppt::array::init<groups_array<Group::value>>(make_group<Group::value>()));

      return result_container(array.begin(), array.end());
    }
  };

public:
  using group_container_array = fcppt::enum_::array<IndexedGroup, result_container>;

  static group_container_array make()
  {
    return fcppt::enum_::array_init<group_container_array>(make_container());
  }
};

}

#endif
