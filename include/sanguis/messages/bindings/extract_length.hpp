#ifndef SANGUIS_MESSAGES_BINDINGS_EXTRACT_LENGTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_EXTRACT_LENGTH_HPP_INCLUDED

#include <sanguis/messages/serialization/endianness.hpp>
#include <fcppt/endianness/copy_n_to_host.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename Concept
>
typename Concept::length_type
extract_length(
	majutsu::concepts::dynamic_memory::tag const *,
	Concept const *,
	majutsu::const_raw_pointer const _memory
)
{
	typedef typename Concept::length_type length_type;

	length_type ret;

	fcppt::endianness::copy_n_to_host(
		_memory,
		sizeof(length_type),
		reinterpret_cast<
			majutsu::raw_pointer
		>(
			&ret
		),
		sizeof(length_type),
		sanguis::messages::serialization::endianness()
	);

	return ret;
}

}
}
}

#endif
