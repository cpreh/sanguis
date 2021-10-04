#ifndef SANGUIS_SERVER_AI_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_AI_STATUS_HPP_INCLUDED

#include <sanguis/server/ai/status_fwd.hpp>


namespace sanguis::server::ai
{

enum class status
{
	running,
	failure,
	success
};

}

#endif
