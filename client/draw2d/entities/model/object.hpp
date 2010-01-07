#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "healthbar_fwd.hpp"
#include "part_fwd.hpp"
#include "parameters_fwd.hpp"
#include "../container.hpp"
#include "../with_health.hpp"
#include "../with_weapon.hpp"
#include "../../sprite/index_fwd.hpp"
#include "../../sprite/order.hpp"
#include "../../sprite/rotation_type.hpp"
#include "../../../health_type.hpp"
#include "../../../vector2.hpp"
#include "../../../../animation_type.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class object 
:
	public container,
	public with_health,
	public with_weapon
{
public:
	object(
		parameters const &,
		fcppt::string const &name,
		sprite::order,
		bool needs_healthbar
	);

	~object();

	// with_health overrides
	health_type
	max_health() const;

	health_type
	health() const;
protected:
	virtual void
	update(
		time_type
	);

	// with_orientation overrides
	virtual void
	orientation(
		sprite::rotation_type
	);

	using container::orientation;

	void
	orientation(
		sprite::rotation_type,
		size_type index
	);
	
	bool
	may_be_removed() const;
	
	// with_speed overrides
	virtual void
	speed(
		vector2 const &
	);

	using container::speed;

	model::part &
	part(
		sprite::index const &
	);

	model::part const &
	part(
		sprite::index const &
	) const;

	bool
	dead() const;

	bool
	walking() const;

	bool
	has_health() const;

	virtual void
	on_decay();
private:
	// with_health overrides
	void
	health(
		health_type
	);

	void
	max_health(
		health_type
	);

	// with_weapon overrides
	void
	weapon(
		weapon_type::type
	);

	void
	attacking(
		bool
	);

	void
	reloading(
		bool
	);


	void
	change_animation();

	void
	change_animation(
		animation_type::type
	);

	animation_type::type
	animation() const;

	animation_type::type
	fallback_anim(
		animation_type::type
	) const;

	void
	update_healthbar();

	bool
	animations_ended() const;

	static fcppt::log::object &
	log();

	bool
		attacking,
		reloading;

	health_type
		health_,
		max_health_;

	fcppt::scoped_ptr<
		healthbar
	> healthbar_;

	typedef boost::ptr_vector<
		part
	> part_vector;

	part_vector parts;
};

}
}
}
}
}

#endif
