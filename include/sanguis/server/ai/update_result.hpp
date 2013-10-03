#ifndef SANGUIS_SERVER_AI_UPDATE_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_AI_UPDATE_RESULT_HPP_INCLUDED

#include <sanguis/server/ai/update_result_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

enum class update_result
{
	new_target,
	keep_target,
	lost_target
};

}
}
}

#endif
