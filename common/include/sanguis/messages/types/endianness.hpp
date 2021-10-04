#ifndef SANGUIS_MESSAGES_TYPES_ENDIANNESS_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_ENDIANNESS_HPP_INCLUDED

#include <alda/serialization/endianness.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <fcppt/config/external_end.hpp>


namespace sanguis::messages::types
{

inline
constexpr
std::endian
endianness()
{
	return
		alda::serialization::endianness();
}

}

#endif
