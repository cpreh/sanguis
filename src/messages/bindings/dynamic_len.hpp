#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include "extract_length.hpp"
#include "put_length.hpp"
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <boost/cstdint.hpp>

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
	bindings::dynamic_len<
		Type,
		Adapted
	> const *,
	Type const &_value
)
{
	majutsu::size_type ret(
		sizeof(
			typename bindings::dynamic_len<
				Type,
				Adapted
			>::length_type
		)
	);

	for(
		typename Type::const_iterator elem_it(
			_value.begin()
		);
		elem_it != _value.end();
		++elem_it
	)
		ret +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				*elem_it
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
	bindings::dynamic_len<
		Type,
		Adapted
	> const *const _concept,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	bindings::put_length(
		_tag,
		_concept,
		_value,
		_mem
	);
	
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
	bindings::dynamic_len<
		Type,
		Adapted
	> const *const _concept,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename bindings::dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type const my_size(
		bindings::extract_length(
			_tag,
			_concept,
			_mem
		)
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
