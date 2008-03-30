#include "types.hpp"
#include <sge/config.h>
#include <sge/codecvt.hpp>

sanguis::messages::string sanguis::messages::host_to_net(const sge::string &s)
{
#ifdef SGE_NARROW_STRING
	return sge::widen(s);
#else
	return s;
#endif
}

sge::string sanguis::messages::net_to_host(const string &s)
{
#ifdef SGE_NARROW_STRING
	return sge::narrow(s);
#else
	return s;
#endif
}
