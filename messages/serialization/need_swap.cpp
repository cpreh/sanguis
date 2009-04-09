#include "need_swap.hpp"
#include "endianness.hpp"
#include <sge/endianness/host_format.hpp>

bool
sanguis::messages::serialization::need_swap()
{
	return endianness() != sge::endianness::host_format();
}
