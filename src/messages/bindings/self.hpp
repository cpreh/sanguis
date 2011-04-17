#ifndef SANGUIS_MESSAGES_BINDINGS_SELF_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_SELF_HPP_INCLUDED

#include "dynamic_len.hpp"
#include "../serialization/endianness.hpp"
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/endianness/copy_n_from_host.hpp>
#include <fcppt/endianness/copy_n_to_host.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename Type
>
struct self
:
bindings::dynamic_len<
	Type,
	Type
>
{
};

template<
	typename Type
>
majutsu::size_type
needed_size(
	majutsu::concepts::dynamic_memory::tag const *,
	bindings::self<
		Type
	> const *,
	Type const &_value
)
{
	return
		sizeof(
			typename bindings::self<
				Type
			>::length_type
		)
		+
		_value.memory().size();
}

template<
	typename Type
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	bindings::self<
		Type
	> const *const _concept,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	typedef typename bindings::self<
		Type
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
	
	fcppt::algorithm::copy_n(
		_value.memory().data(),
		_value.memory().size(),
		_mem
	);
}

template<
	typename Type
>
Type 
make(
	majutsu::concepts::dynamic_memory::tag const *,
	bindings::self<
		Type
	> const *,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename bindings::self<
		Type
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

	fcppt::algorithm::copy_n(
		_mem,
		my_size,
		ret.memory().data()
	);

	return ret;
}

}
}
}

#endif
