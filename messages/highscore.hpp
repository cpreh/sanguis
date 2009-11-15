#ifndef SANGUIS_MESSAGES_HIGHSCORE_HPP_INCLUDED
#define SANGUIS_MESSAGES_HIGHSCORE_HPP_INCLUDED

#include "make_class.hpp"
#include "make_message_id.hpp"
#include "string_vector.hpp"
#include "score_type.hpp"
#include "roles/highscore.hpp"
#include "types/message.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector3<
		make_message_id<
			types::message::highscore
		>::type,
		majutsu::role<
			string_vector
		>,
		majutsu::role<
			score_type,
			roles::highscore
		>
	>
> highscore_elements;

typedef make_class<
	highscore_elements
>::type highscore;

}
}

#endif
