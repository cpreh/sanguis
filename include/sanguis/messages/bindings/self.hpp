#ifndef SANGUIS_MESSAGES_BINDINGS_SELF_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_SELF_HPP_INCLUDED

#include <alda/bindings/dynamic_len.hpp>
// TODO:
#include <alda/bindings/detail/extract_length.hpp>
// TODO:
#include <alda/bindings/detail/put_length.hpp>
// TODO:
#include <alda/serialization/detail/read/make_object.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <fcppt/config/external_end.hpp>

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
alda::bindings::dynamic_len<
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
	alda::bindings::detail::put_length(
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
		alda::bindings::detail::extract_length(
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
		alda::serialization::detail::read::make_object<
			Type
		>(
			stream
		);
}

}
}
}

#endif
