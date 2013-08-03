#ifndef SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED

#include <alda/message/make_class.hpp>


namespace sanguis
{
namespace messages
{

template<
	typename T
>
using make_class
=
alda::message::make_class<
	T
>;

}
}

#endif
