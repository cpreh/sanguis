#ifndef SANGUIS_MESSAGES_SERIALIZATION_LOAD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_LOAD_HPP_INCLUDED

#include "raw_container.hpp"
#include "istream.hpp"
#include "endianness.hpp"
#include "../bindings/dynamic_len.hpp"
#include <sge/container/raw_vector_impl.hpp>
#include <sge/io/read.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename Type
>
struct load {
	static typename Type::type
	get(
		istream &is)
	{
		typename Type::type ret;

		raw_container vec(
			Type::needed_size(
				ret
			)
		);

		is.read(
			reinterpret_cast<char *>(vec.data()),
			vec.size()
		);

		return Type::make(
			vec.data(),
			vec.size()
		);
	}
};

template<
	typename T,
	template<
		typename
	> class A
>
struct load<
	bindings::dynamic_len<
		T,
		A
	>
> {
	static typename bindings::dynamic_len<T, A>::type
	get(
		istream &is)
	{
		typedef bindings::dynamic_len<T, A> type;
		typename type::type ret;

		majutsu::size_type const length_sz(
			sizeof(typename type::length_type)
		);

		typedef typename type::length_type length_type;

		length_type const sz(
			sge::io::read<
				length_type
			>(
				is,
				endianness()
			)
		);
		
		raw_container vec(
			sz + length_sz
		);

		is.read(
			reinterpret_cast<char *>(vec.data() + length_sz),
			sz
		);

		return type::make(
			vec.data(),
			vec.size()
		);
	}
};

}
}
}

#endif
