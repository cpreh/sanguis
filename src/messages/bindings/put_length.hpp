#ifndef SANGUIS_MESSAGES_BINDINGS_PUT_LENGTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_PUT_LENGTH_HPP_INCLUDED

#include "../serialization/endianness.hpp"
#include <fcppt/endianness/copy_n_from_host.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/raw_pointer.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename Concept,
	typename Type
>
void
put_length(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	Concept const *const _concept,
	Type const &_value,
	majutsu::raw_pointer &_memory
)
{
	typedef typename Concept::length_type length_type;

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
		_memory,
		sizeof(length_type),
		sanguis::messages::serialization::endianness()
	);

	_memory += sizeof(length_type);
}

}
}
}

#endif

