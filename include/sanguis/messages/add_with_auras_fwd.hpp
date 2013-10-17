#ifndef SANGUIS_MESSAGES_ADD_WITH_AURAS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WITH_AURAS_FWD_HPP_INCLUDED

#include <sanguis/messages/add_with_weapon_fwd.hpp>
#include <sanguis/messages/adapted_types/aura_type_vector_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
majutsu::composite<
	boost::mpl::vector2<
		sanguis::messages::add_with_weapon,
		majutsu::role<
			sanguis::messages::adapted_types::aura_type_vector
		>
	>
>
add_with_auras;

}
}

#endif
