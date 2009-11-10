#ifndef SANGUIS_MESSAGES_BINDINGS_STATIC_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_STATIC_HPP_INCLUDED

#include <majutsu/concepts/dynamic_memory.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename T,
	typename Adapted
>
struct static_ {
	typedef T type;
};

}
}
}

namespace majutsu
{
namespace concepts
{

template<
	typename T,
	typename Adapted
>
struct dynamic_memory<
	sanguis::messages::bindings::static_<
		T,
		Adapted
	>
>
{
private:
	typedef T type;
	typedef dynamic_memory<
		Adapted
	> adapted;
public:
	static majutsu::size_type
	static_size()
	{
		return
			type::dim_wrapper::value
			* sizeof(typename T::value_type);
	}

	static majutsu::size_type
	needed_size(
		type const &
	)
	{
		return static_size();
	}

	static void
	place(
		type const &t,
		majutsu::raw_pointer mem
	)
	{
		for(
			typename type::const_iterator it(
				t.begin()
			);
			it != t.end();
			mem += adapted::needed_size(*it),
			++it
		)
			adapted::place(
				*it,
				mem
			);
	}

	static type
	make(
		majutsu::const_raw_pointer mem
	)
	{
		type ret;

		for(
			typename type::iterator it(
				ret.begin()
			);
			it != ret.end();
			mem += adapted::needed_size(*it),
			++it
		)
			*it = adapted::make(
				mem
			);

		return ret;
	}
};

}
}

#endif
