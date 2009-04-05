#ifndef SANGUIS_MESSAGES_SERIALIZATION_LOAD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_LOAD_HPP_INCLUDED

#include "raw_container.hpp"
#include "istream.hpp"
#include "../bindings/dynamic_len.hpp"
#include <sge/container/raw_vector_impl.hpp>

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
	typename T
>
struct load<
	bindings::dynamic_len<
		T
	>
> {
	static typename bindings::dynamic_len<T>::type
	get(
		istream &is)
	{
		typename bindings::dynamic_len<T>::type ret;

		raw_container vec;

		majutsu::size_type const length_sz(
			sizeof(typename bindings::dynamic_len<T>::length_type)
		);

		typename bindings::dynamic_len<T>::length_type sz;
		is.read(reinterpret_cast<char *>(&sz), length_sz);

		vec.resize(
			sz + length_sz
		);

		is.read(
			reinterpret_cast<char *>(vec.data() + length_sz),
			sz
		);

		return bindings::dynamic_len<T>::make(
			vec.data(),
			vec.size()
		);
	}
};

}
}
}

#endif
