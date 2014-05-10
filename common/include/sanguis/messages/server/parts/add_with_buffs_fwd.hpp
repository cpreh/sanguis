#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_BUFFS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_BUFFS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/buff_type_vector_fwd.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
majutsu::composite<
	boost::mpl::vector1<
		majutsu::role<
			sanguis::messages::adapted_types::buff_type_vector,
			sanguis::messages::roles::buff_type_container
		>
	>
>
add_with_buffs;

}
}
}
}

#endif
