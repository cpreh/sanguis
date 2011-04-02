#ifndef SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_STRONG_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_STRONG_HPP_INCLUDED

#include "fundamental.hpp"
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename T
>
struct fundamental_strong 
{
	typedef T type;
};

template<
	typename Type
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	bindings::fundamental_strong<
		Type
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			bindings::fundamental<
				typename Type::value_type
			> const *
		>(
			0
		),
		_type.get(),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	bindings::fundamental_strong<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		Type(
			make(
				_tag,
				static_cast<
					bindings::fundamental<
						typename Type::value_type
					> const *
				>(
					0
				),
				_beg
			)
		);
}

}
}
}

namespace majutsu
{
namespace concepts
{

template<
	typename Type
>
struct static_size<
	sanguis::messages::bindings::fundamental_strong<
		Type
	>
>
:
static_size<
	sanguis::messages::bindings::fundamental<
		typename Type::value_type
	>
>
{};

}
}

#endif
