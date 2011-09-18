#ifndef SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_FUNDAMENTAL_HPP_INCLUDED

#include <sanguis/messages/bindings/float.hpp>
#include <sanguis/messages/serialization/endianness.hpp>
#include <sanguis/messages/types/space_unit.hpp>
#include <fcppt/endianness/to_host.hpp>
#include <fcppt/endianness/from_host.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/fundamental.hpp>
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
struct fundamental
:
majutsu::fundamental<
	T
>
{};

template<>
struct fundamental<
	float
>
:
float_
{};

template<
	typename Type
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	bindings::fundamental<
		Type
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			majutsu::fundamental<
				Type
			> const *
		>(
			0
		),
		fcppt::endianness::from_host(
			_type,
			sanguis::messages::serialization::endianness()
		),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	bindings::fundamental<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::endianness::to_host(
			make(
				_tag,
				static_cast<
					majutsu::fundamental<
						Type
					> const *
				>(
					0
				),
				_beg
			),
			sanguis::messages::serialization::endianness()
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
	sanguis::messages::bindings::fundamental<
		Type
	>
>
:
static_size<
	majutsu::fundamental<
		Type
	>
>
{};

}
}

#endif
