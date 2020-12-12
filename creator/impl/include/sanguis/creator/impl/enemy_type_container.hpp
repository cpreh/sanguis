#ifndef SANGUIS_CREATOR_IMPL_ENEMY_TYPE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_ENEMY_TYPE_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/enemy_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

using
enemy_type_container
=
std::vector<
	sanguis::creator::enemy_type
>;

}
}
}

#endif
