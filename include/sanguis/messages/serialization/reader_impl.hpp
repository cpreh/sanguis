#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED

#include <sanguis/messages/serialization/reader.hpp>
#include <sanguis/messages/serialization/make_object.hpp>
#include <sanguis/messages/make_concrete.hpp>

template<
	typename Msg
>
sanguis::messages::auto_ptr
sanguis::messages::serialization::reader::operator()() const
{
	return
		messages::make_concrete(
			messages::serialization::make_object<
				Msg
			>(
				is_
			)
		);
}

#endif
