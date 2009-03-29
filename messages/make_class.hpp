#ifndef SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED

#include <sge/restrict_typedef_struct.hpp>
#include <majutsu/class.hpp>
#include <majutsu/memory/flat.hpp>

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
		majutsu::memory::flat
	> type;

	SGE_RESTRICT_TYPEDEF_STRUCT(make_class)
};

}
}

#endif
