#ifndef SANGUIS_MESSAGES_BINDINGS_FLOAT_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_FLOAT_HPP_INCLUDED

#include "../types/space_unit.hpp"
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

struct float_
:
majutsu::fundamental<
	types::space_unit
>
{};

majutsu::size_type
needed_size(
	majutsu::concepts::dynamic_memory::tag const *,
	float_ const *,
	float_::type const &
);

void
place(
	majutsu::concepts::dynamic_memory::tag const *,
	float_ const *,
	float_::type const &,
	majutsu::raw_pointer
);

float_::type
make(
	majutsu::concepts::dynamic_memory::tag const *,
	float_ const *,
	majutsu::const_raw_pointer
);

}
}
}

namespace majutsu
{
namespace concepts
{

template<>
struct static_size<
	sanguis::messages::bindings::float_
>
:
static_size<
	majutsu::fundamental<
		sanguis::messages::types::space_unit
	>
>
{};

}
}

#endif
