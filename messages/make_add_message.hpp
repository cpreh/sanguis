#ifndef SANGUIS_MESSAGES_MAKE_ADD_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_ADD_MESSAGE_HPP_INCLUDED

#include "roles/pos.hpp"
#include "roles/angle.hpp"
#include "roles/speed.hpp"
#include "roles/health.hpp"
#include "roles/max_health.hpp"
#include "types/message.hpp"
#include "bind_entity_message.hpp"
#include "space_unit.hpp"
#include "vector2.hpp"
#include "pos.hpp"
#include "dim.hpp"
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

template<
	types::message::type Msg,
	typename AdditionalElements
>
struct make_add_message {
	typedef boost::mpl::vector<
		typename bind_entity_message<
			Msg
		>::type,
		majutsu::role<
			pos,
			roles::pos
		>,
		majutsu::role<
			space_unit,
			roles::angle
		>,
		majutsu::role<
			vector2,
			roles::speed
		>,
		majutsu::role<
			space_unit,
			roles::health
		>,
		majutsu::role<
			space_unit,
			roles::max_health
		>,
		majutsu::role<
			dim
		>
	> common_elements;
private:
	typedef majutsu::composite<
		boost::mpl::copy<
			AdditionalElements,
			boost::mpl::back_inserter<
				common_elements
			>
		>
	> type;
};

}
}

#endif
