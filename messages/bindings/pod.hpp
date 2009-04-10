#ifndef SANGUIS_SERIALIZATION_BINDINGS_POD_HPP_INCLUDED
#define SANGUIS_SERIALIZATION_BINDINGS_POD_HPP_INCLUDED

#include "float.hpp"
#include "../serialization/endianness.hpp"
#include "../types/space_unit.hpp"
#include <sge/endianness/to_host.hpp>
#include <sge/endianness/from_host.hpp>
#include <majutsu/pod.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename T
>
struct pod {
private:
	typedef majutsu::pod<T> adapted;
public:
	typedef T type;

	static majutsu::size_type
	needed_size(
		type const &t)
	{
		return adapted::needed_size(t); 
	}

	static void
	place(
		type const &t,
		majutsu::raw_pointer const mem)
	{
		adapted::place(
			sge::endianness::from_host(
				t,
				serialization::endianness()
			),
			mem
		);
	}

	static type
	make(
		majutsu::const_raw_pointer const beg,
		majutsu::size_type const sz)
	{
		return sge::endianness::to_host(
			adapted::make(
				beg,
				sz
			),
			serialization::endianness()
		);
	}
};

template<>
struct pod<
	types::space_unit
>
:
float_
{};

}
}
}

#endif
