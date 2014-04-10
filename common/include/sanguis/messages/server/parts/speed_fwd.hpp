#ifndef SANGUIS_MESSAGES_SERVER_PARTS_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_SPEED_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/roles/speed.hpp>
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
			sanguis::messages::adapted_types::vector2,
			sanguis::messages::roles::speed
		>
	>
>
speed;

}
}
}
}

#endif
