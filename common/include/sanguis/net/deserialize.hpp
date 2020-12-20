#ifndef SANGUIS_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_NET_DESERIALIZE_HPP_INCLUDED

#include <sanguis/net/message_header.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/net/buffer/circular_receive/extract_message.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
inline
fcppt::optional::object<
	alda::message::base_unique_ptr<
		AldaType
	>
>
deserialize(
	alda::serialization::context<
		AldaType
	> const &_context,
	alda::net::buffer::circular_receive::streambuf &_data // NOLINT(google-runtime-references)
) // NOLINT(google-runtime-references)
{
	return
		alda::net::buffer::circular_receive::extract_message<
			sanguis::net::message_header
		>(
			_context,
			_data
		);
}

}
}

#endif
