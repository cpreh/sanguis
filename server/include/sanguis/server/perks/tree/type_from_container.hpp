#ifndef SANGUIS_SERVER_PERKS_TREE_TYPE_FROM_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_TYPE_FROM_CONTAINER_HPP_INCLUDED

#include <sanguis/server/perks/tree/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

template<
	typename Container
>
using type_from_container
=
typename
boost::mpl::if_<
	std::is_const<
		Container
	>,
	sanguis::server::perks::tree::object const,
	sanguis::server::perks::tree::object
>::type;

}
}
}
}

#endif
