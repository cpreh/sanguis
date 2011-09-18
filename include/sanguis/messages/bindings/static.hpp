#ifndef SANGUIS_MESSAGES_BINDINGS_STATIC_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_STATIC_HPP_INCLUDED

#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/integral_size.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>

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
struct static_
{
	typedef Type type;
};

template<
	typename Type,
	typename Adapted
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	static_<
		Type,
		Adapted
	> const *,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
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
	static_<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer _mem
)
{
	Type ret;

	for(
		typename Type::iterator it(
			ret.begin()
		);
		it != ret.end();
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
		*it =
			make(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				_mem
			);

	return ret;
}

}
}
}

namespace majutsu
{
namespace concepts
{

template<
	typename Type,
	typename Adapted
>
struct static_size<
	sanguis::messages::bindings::static_<
		Type,
		Adapted
	>
>
:
majutsu::integral_size<
	Type::dim_wrapper::value
	* sizeof(typename Type::value_type)
>
{};

}
}

#endif
