#ifndef SANGUIS_SERVER_AI_TREE_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_STATUS_HPP_INCLUDED

#include <sanguis/server/ai/tree/status.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

enum class status
{
	ended_failure,
	ended_success,
	running
};

}
}
}
}

#endif
