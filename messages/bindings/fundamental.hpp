#ifndef SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_HPP_INCLUDED

#include "float.hpp"
#include "../serialization/endianness.hpp"
#include "../types/space_unit.hpp"
#include <sge/endianness/to_host.hpp>
#include <sge/endianness/from_host.hpp>
#include <majutsu/concepts/dynamic_memory.hpp>
#include <majutsu/fundamental.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename T
>
struct fundamental
:
majutsu::fundamental<
	T
>
{};

}
}
}

namespace majutsu
{
namespace concepts
{

template<
	typename T
>
struct dynamic_memory<
	sanguis::messages::bindings::fundamental<
		T
	>
>
{
private:
	typedef T type;

	typedef dynamic_memory<
		majutsu::fundamental<
			T
		>
	> adapted;
public:
	static majutsu::size_type
	needed_size(
		type const &t
	)
	{
		return adapted::needed_size(
			t
		); 
	}

	static void
	place(
		type const &t,
		majutsu::raw_pointer const mem
	)
	{
		adapted::place(
			sge::endianness::from_host(
				t,
				sanguis::messages::serialization::endianness()
			),
			mem
		);
	}

	static type
	make(
		majutsu::const_raw_pointer const beg
	)
	{
		return sge::endianness::to_host(
			adapted::make(
				beg
			),
			sanguis::messages::serialization::endianness()
		);
	}
};

template<>
struct dynamic_memory<
	sanguis::messages::bindings::fundamental<
		sanguis::messages::types::space_unit
	>
>
:
sanguis::messages::bindings::float_
{};

}
}

#endif
