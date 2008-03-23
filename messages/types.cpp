#include "types.hpp"
#include <sge/codecvt.hpp>

sanguis::messages::string sanguis::messages::host_to_net(const sge::string &s)
{
#ifdef SGE_NARROW_STRING
	return sge::widen(s);
#else
	return s;
#endif
}
