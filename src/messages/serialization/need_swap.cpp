#include "need_swap.hpp"
#include "endianness.hpp"
#include <fcppt/endianness/host_format.hpp>

bool
sanguis::messages::serialization::need_swap()
{
	return endianness() != fcppt::endianness::host_format();
}