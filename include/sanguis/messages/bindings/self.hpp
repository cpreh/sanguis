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
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

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

FCPPT_PP_POP_WARNING

template<
	typename Type
>
majutsu::size_type
needed_size(
	sanguis::messages::bindings::self<
		Type
	> const *,
	Type const &_value
)
{
	return
		sizeof(
			typename sanguis::messages::bindings::self<
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
	sanguis::messages::bindings::self<
		Type
	> const *const _concept,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	alda::bindings::detail::put_length(
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
	sanguis::messages::bindings::self<
		Type
	> const *const _concept,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename sanguis::messages::bindings::self<
		Type
	>::length_type length_type;

	length_type const length(
		alda::bindings::detail::extract_length(
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
