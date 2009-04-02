#ifndef SANGUIS_MESSAGES_BINDINGS_STATIC_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_STATIC_HPP_INCLUDED

#include <majutsu/detail/copy_n.hpp> // TODO: replace this
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename T
>
struct static_ {
	typedef T type;

	static majutsu::size_type
	needed_size(
		type const &t)
	{
		return t.size() * sizeof(typename T::value_type); 
	}

	static void
	place(
		type const &t,
		majutsu::raw_pointer const mem)
	{
		majutsu::detail::copy_n(
			reinterpret_cast<
				majutsu::const_raw_pointer
			>(
				t.data()
			),
			t.size() * sizeof(typename T::value_type),
			mem
		);
	}

	static type
	make(
		majutsu::const_raw_pointer const beg,
		majutsu::size_type const sz)
	{
		type ret;

		majutsu::detail::copy_n(
			beg,
			sz,
			reinterpret_cast<
				majutsu::raw_pointer
			>(
				ret.data()
			)
		);
	}
};

}
}
}

#endif
