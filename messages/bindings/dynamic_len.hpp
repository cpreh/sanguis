#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include "../../truncation_check_cast.hpp"
#include "../serialization/endianness.hpp"
#include <sge/endianness/copy_n_from_host.hpp>
#include <sge/endianness/copy_n_to_host.hpp>
#include <sge/assert.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>

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
struct dynamic_len {
	typedef T type;

	typedef Adapted adapted;

	typedef boost::uint16_t length_type;

	static majutsu::size_type
	needed_size(
		type const &t)
	{
		majutsu::size_type ret(
			sizeof(length_type)
		);

		BOOST_FOREACH(
			typename T::const_reference r,
			t
		)
			ret += adapted::needed_size(r);

		return ret;
	}

	static void
	place(
		type const &t,
		majutsu::raw_pointer mem)
	{
		length_type const sz(
			truncation_check_cast<length_type>(
				needed_size(t)
			)
		);

		sge::endianness::copy_n_from_host(
			reinterpret_cast<
				majutsu::const_raw_pointer
			>(
				&sz
			),
			sizeof(length_type),
			mem,
			sizeof(length_type),
			serialization::endianness()
		);

		mem += sizeof(length_type);
		
		for(
			typename type::const_iterator it(t.begin());
			it != t.end();
			mem += adapted::needed_size(*it), ++it
		)
			adapted::place(
				*it,
				mem
			);
	}

	static type 
	make(
		majutsu::const_raw_pointer const mem)
	{
		length_type my_size;
		
		sge::endianness::copy_n_to_host(
			mem,
			sizeof(length_type),
			reinterpret_cast<
				majutsu::raw_pointer
			>(
				&my_size
			),
			sizeof(length_type),
			serialization::endianness()
		);
		
		type ret;

		for(
			majutsu::const_raw_pointer cur_mem(
				mem + sizeof(length_type)
			);
			cur_mem != mem + my_size;
		)
		{
			typename T::value_type elem(
				adapted::make(
					cur_mem
				)
			);

			ret.push_back(
				elem
			);

			cur_mem += adapted::needed_size(elem);
		}

		return ret;
	}
};

}
}
}

#endif
