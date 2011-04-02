#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include "../serialization/endianness.hpp"
#include <fcppt/endianness/copy_n_from_host.hpp>
#include <fcppt/endianness/copy_n_to_host.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/const_raw_pointer.hpp>
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
	typename Type,
	typename Adapted
>
struct dynamic_len
{
	typedef Type type;

	typedef boost::uint16_t length_type;
};

template<
	typename Type,
	typename Adapted
>
majutsu::size_type
needed_size(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	dynamic_len<
		Type,
		Adapted
	> const *,
	Type const &_value
)
{
	majutsu::size_type ret(
		sizeof(
			typename dynamic_len<
				Type,
				Adapted
			>::length_type
		)
	);

	BOOST_FOREACH(
		typename Type::const_reference elem,
		_value
	)
		ret +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				elem
			);

	return ret;
}

template<
	typename Type,
	typename Adapted
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	dynamic_len<
		Type,
		Adapted
	> const *const _concept,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	typedef typename dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type const sz(
		fcppt::truncation_check_cast<
			length_type
		>(
			needed_size(
				_tag,
				_concept,
				_value
			)
		)
	);

	fcppt::endianness::copy_n_from_host(
		reinterpret_cast<
			majutsu::const_raw_pointer
		>(
			&sz
		),
		sizeof(length_type),
		_mem,
		sizeof(length_type),
		sanguis::messages::serialization::endianness()
	);

	_mem += sizeof(length_type);
	
	for(
		typename Type::const_iterator it(
			_value.begin()
		);
		it != _value.end();
		_mem +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				*it
			),
		++it
	)
		place(
			_tag,
			static_cast<
				Adapted const *
			>(0),
			*it,
			_mem
		);
}

template<
	typename Type,
	typename Adapted
>
Type 
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	dynamic_len<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type my_size;
		
	fcppt::endianness::copy_n_to_host(
		_mem,
		sizeof(length_type),
		reinterpret_cast<
			majutsu::raw_pointer
		>(
			&my_size
		),
		sizeof(length_type),
		sanguis::messages::serialization::endianness()
	);
		
	Type ret;

	for(
		majutsu::const_raw_pointer cur_mem(
			_mem + sizeof(length_type)
		);
		cur_mem != _mem + my_size;
	)
	{
		typename Type::value_type elem(
			make(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				cur_mem
			)
		);

		ret.push_back(
			elem
		);

		cur_mem +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				elem
			);
	}

	return ret;
}

}
}
}

#endif
