#ifndef SANGUIS_SERVER_AI_SWARM_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SWARM_HPP_INCLUDED

#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class swarm
:
	public sanguis::server::ai::simple
{
	FCPPT_NONCOPYABLE(
		swarm
	);
public:
	swarm(
		sanguis::server::entities::with_ai &,
		sanguis::server::ai::sight_range
	);

	~swarm();
private:
};

}
}
}

#endif
