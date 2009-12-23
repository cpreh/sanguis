#ifndef SANGUIS_MESSAGES_SERIALIZATION_LOAD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_LOAD_HPP_INCLUDED

#include "raw_container.hpp"
#include "istream.hpp"
#include "endianness.hpp"
#include "../bindings/dynamic_len.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <sge/algorithm/copy_n.hpp>
#include <fcppt/io/read.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>

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
		istream &is
	)
	{
		typename Type::type ret;

		raw_container vec(
			needed_size(
				static_cast<
					majutsu::concepts::dynamic_memory::tag const *
				>(0),
				static_cast<
					Type const *
				>(0),
				ret
			)
		);

		is.read(
			reinterpret_cast<char *>(vec.data()),
			vec.size()
		);

		return
			make(
				static_cast<
					majutsu::concepts::dynamic_memory::tag const *
				>(0),
				static_cast<
					Type const *
				>(0),
				vec.data()
			);
	}
};

template<
	typename T,
	typename A
>
struct load<
	bindings::dynamic_len<
		T,
		A
	>
> {
	static typename bindings::dynamic_len<T, A>::type
	get(
		istream &is
	)
	{
		typedef bindings::dynamic_len<T, A> type;

		typename type::type ret;

		majutsu::size_type const length_sz(
			sizeof(typename type::length_type)
		);

		typedef typename type::length_type length_type;

		length_type const sz(
			fcppt::io::read<
				length_type
			>(
				is,
				endianness()
			)
		);
		
		raw_container vec(
			sz + length_sz
		);

		sge::algorithm::copy_n(
			reinterpret_cast<
				raw_container::const_pointer
			>(
				&sz
			),
			sizeof(length_type),
			vec.data()
		);

		is.read(
			reinterpret_cast<char *>(vec.data() + length_sz),
			sz - length_sz
		);

		return
			make(
				static_cast<
					majutsu::concepts::dynamic_memory::tag const *
				>(0),
				static_cast<
					type const *
				>(0),
				vec.data()
			);
	}
};

}
}
}

#endif
