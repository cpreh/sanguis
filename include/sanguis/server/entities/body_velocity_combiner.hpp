#ifndef SANGUIS_SERVER_ENTITIES_BODY_VELOCITY_COMBINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BODY_VELOCITY_COMBINER_HPP_INCLUDED

#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_body.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class body_velocity_combiner
:
	public virtual sanguis::server::entities::ifaces::with_body,
	public virtual sanguis::server::entities::ifaces::with_velocity
{
	FCPPT_NONCOPYABLE(
		body_velocity_combiner
	);
public:
	body_velocity_combiner();

	~body_velocity_combiner();
private:
	void
	on_speed_change(
		sanguis::server::speed const &
	)
	override
	final;

	sanguis::server::speed const
	initial_speed() const
	override
	final;

	sanguis::server::speed const
	actual_speed() const
	override
	final;
};

}
}
}

#endif
