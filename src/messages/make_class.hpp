#ifndef SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED

#include <majutsu/memory/raw.hpp>
#include <majutsu/class.hpp>

namespace sanguis
{
namespace messages
{

template<
	typename T
>
struct make_class
{
	typedef majutsu::class_<
		T,
		majutsu::memory::raw
	> type;
};

}
}

#endif
