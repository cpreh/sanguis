#ifndef SANGUIS_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add,
	boost::mpl::vector<>
>::type add_elements;

typedef make_class<
	add_elements
>::type add;

}
}

#endif
