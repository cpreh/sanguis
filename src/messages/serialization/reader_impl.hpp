#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED

#include "reader.hpp"
#include "make_object.hpp"
#include "../make_concrete.hpp"

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
