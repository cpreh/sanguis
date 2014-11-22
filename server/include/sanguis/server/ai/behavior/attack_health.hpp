#ifndef SANGUIS_SERVER_AI_BEHAVIOR_ATTACK_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_ATTACK_HEALTH_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

class attack_health
:
	public sanguis::server::ai::behavior::attack
{
	FCPPT_NONCOPYABLE(
		attack_health
	);
public:
	attack_health(
		sanguis::server::ai::context &,
		sanguis::server::ai::sight_range,
		sanguis::server::ai::speed_factor
	);

	~attack_health()
	override;
private:
	sanguis::server::ai::speed_factor const
	speed_factor() const
	override;

	sanguis::server::ai::speed_factor const speed_factor_;
};

}
}
}
}

#endif
