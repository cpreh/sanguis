#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include "../../truncation_check_cast.hpp"
#include "../serialization/endianness.hpp"
#include <sge/endianness/copy_n_from_host.hpp>
#include <sge/assert.hpp>
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
	typename T,
	template<
		typename 
	> class Adapted
>
struct dynamic_len {
	typedef T type;

	typedef Adapted<typename T::value_type> adapted;

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
		majutsu::raw_pointer mem)
	{
		length_type const sz(
			truncation_check_cast<length_type>(
				t.size()
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
		majutsu::const_raw_pointer mem,
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

		mem += sizeof(length_type);

		for(
			typename type::iterator it(ret.begin());
			it != ret.end();
			mem += adapted::needed_size(*it), ++it
		)
			*it = adapted::make(
				mem,
				sizeof(typename T::value_type)
			);

		return ret;
	}
};


}
}
}

#endif
