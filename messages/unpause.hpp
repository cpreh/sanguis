#ifndef SANGUIS_MESSAGES_UNPAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_UNPAUSE_HPP_INCLUDED

#include "types/message.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/constant.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		majutsu::constant<
			types::message::type,
			types::message::unpause
		>
	>
> unpause_elements;

typedef make_class<
	unpause_elements
>::type unpause;

}
}

#endif
