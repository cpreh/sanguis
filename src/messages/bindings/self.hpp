#ifndef SANGUIS_MESSAGES_BINDINGS_SELF_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_SELF_HPP_INCLUDED

#include "dynamic_len.hpp"
#include "extract_length.hpp"
#include "put_length.hpp"
#include "../serialization/make_object.hpp"
#include <fcppt/algorithm/copy_n.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>

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
	bindings::put_length(
		_tag,
		_concept,
		_value,
		_mem
	);
	
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
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	bindings::self<
		Type
	> const *const _concept,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename bindings::self<
		Type
	>::length_type length_type;

	length_type const length(
		bindings::extract_length(
			_tag,
			_concept,
			_mem
		)
	);

	typedef boost::iostreams::stream_buffer<
		boost::iostreams::array_source
	> streambuf;

	streambuf buffer(
		reinterpret_cast<
			char const *
		>(
			_mem + sizeof(length_type)
		),
		length  - sizeof(length_type)
	);

	std::istream stream(
		&buffer
	);

	return 
		messages::serialization::make_object<
			Type
		>(
			stream
		);
}

}
}
}

#endif
