#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/detail/copy_n.hpp> // TODO: replace this

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename T
>
struct dynamic_len {
	typedef T type;

	typedef boost::uint16_t length_type;

	static majutsu::size_type
	needed_size(
		type const &t)
	{
		return t.size() + sizeof(length_type);
	}

	static void
	place(
		type const &t,
		majutsu::raw_pointer const mem)
	{
		// TODO: check truncation
		length_type const sz(
			static_cast<length_type>(
				t.size()
			)
		);

		majutsu::detail::copy_n(
			reinterpret_cast<
				majutsu::const_raw_pointer
			>(
				&sz
			),
			sizeof(length_type),
			mem
		);
			
		majutsu::detail::copy_n(
			reinterpret_cast<
				majutsu::const_raw_pointer
			>(
				t.data()
			),
			t.size(),
			mem + sizeof(length_type)
		);
	}

	static type 
	make(
		majutsu::const_raw_pointer const beg,
		majutsu::size_type const sz)
	{
		type ret;
		
		ret.resize(
			sz / sizeof(typename type::value_type)
		);

		majutsu::detail::copy_n(
			beg + sizeof(length_type),
			sz - sizeof(length_type),
			reinterpret_cast<
				majutsu::raw_pointer
			>(
				const_cast<
					char *
				>(ret.data())
			)
		);

		return ret;
	}
};


}
}
}

#endif
