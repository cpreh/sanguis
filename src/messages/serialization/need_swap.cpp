#include <sanguis/messages/serialization/need_swap.hpp>
#include <sanguis/messages/serialization/endianness.hpp>
#include <fcppt/endianness/host_format.hpp>

bool
sanguis::messages::serialization::need_swap()
{
	return serialization::endianness() != fcppt::endianness::host_format();
}
