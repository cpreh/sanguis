#ifndef SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_STRONG_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_STRONG_HPP_INCLUDED

#include <alda/bindings/fundamental.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/read/load.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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
	sanguis::messages::bindings::fundamental_strong<
		Type
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			alda::bindings::fundamental<
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
	sanguis::messages::bindings::fundamental_strong<
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
					alda::bindings::fundamental<
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

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
	alda::bindings::fundamental<
		typename Type::value_type
	>
>
{};

FCPPT_PP_POP_WARNING

}
}

namespace alda
{
namespace serialization
{
namespace detail
{
namespace read
{

template<
	typename Type
>
struct load<
	sanguis::messages::bindings::fundamental_strong<
		Type
	>
>
{
	static typename
	sanguis::messages::bindings::fundamental_strong<
		Type
	>::type const
	get(
		alda::serialization::istream &_is
	)
	{
		return
			typename
			sanguis::messages::bindings::fundamental_strong<
				Type
			>::type(
				alda::serialization::detail::read::load<
					alda::bindings::fundamental<
						typename Type::value_type
					>
				>::get(
					_is
				)
			);
	}
};

}
}
}
}

#endif
