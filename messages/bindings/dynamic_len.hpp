#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <sge/assert.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <majutsu/detail/copy_n.hpp> // TODO: replace this
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <boost/cstdint.hpp>

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
		return t.size() * sizeof(typename T::value_type) + sizeof(length_type);
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
			t.size() * sizeof(typename T::value_type),
			mem + sizeof(length_type)
		);
	}

	static type 
	make(
		majutsu::const_raw_pointer const beg,
		majutsu::size_type const sz)
	{
		SGE_ASSERT(sz > sizeof(length_type));

		majutsu::size_type const sz_wo_len(
			sz - sizeof(length_type)
		);

		SGE_ASSERT(sz_wo_len % sizeof(typename type::value_type) == 0);

		type ret;
		
		ret.resize(
			sz_wo_len / sizeof(typename type::value_type)
		);

		majutsu::detail::copy_n(
			beg + sizeof(length_type),
			sz_wo_len,
			reinterpret_cast<
				majutsu::raw_pointer
			>(
				// TODO: make this better!
				// This works with basic_string and raw_vector
				const_cast<
					typename type::value_type *	
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
