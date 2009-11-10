#ifndef SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED

#include <sge/restrict_typedef_struct.hpp>
#include <majutsu/memory/raw.hpp>
#include <majutsu/class.hpp>

namespace sanguis
{
namespace messages
{

template<
	typename T
>
struct make_class {
	typedef majutsu::class_<
		T,
		majutsu::memory::raw
	> type;

	SGE_RESTRICT_TYPEDEF_STRUCT(make_class)
};

}
}

#endif
