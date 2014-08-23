#ifndef SANGUIS_SERVER_AI_BEHAVIOR_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/ai/behavior/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

typedef
std::unique_ptr<
	sanguis::server::ai::behavior::base
>
base_unique_ptr;

}
}
}
}

#endif
