#ifndef SANGUIS_SERVER_AI_OPTIONAL_TARGET_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_AI_OPTIONAL_TARGET_FWD_HPP_INCLUDED

#include <sanguis/server/ai/target_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

typedef
fcppt::optional<
	sanguis::server::ai::target
>
optional_target;

}
}
}

#endif
