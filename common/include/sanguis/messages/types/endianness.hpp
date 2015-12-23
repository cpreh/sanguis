#ifndef SANGUIS_MESSAGES_TYPES_ENDIANNESS_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_ENDIANNESS_HPP_INCLUDED

#include <alda/serialization/endianness.hpp>
#include <fcppt/endianness/format.hpp>


namespace sanguis
{
namespace messages
{
namespace types
{

inline
constexpr
fcppt::endianness::format
endianness()
{
	return
		alda::serialization::endianness();
}

}
}
}

#endif
