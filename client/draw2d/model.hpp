#ifndef SANGUIS_DRAW_MODEL_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_HPP_INCLUDED

#include "sprite_part_index_fwd.hpp"
#include "environment_fwd.hpp"
#include "model_part_fwd.hpp"
#include "container.hpp"
#include "healthbar.hpp"
#include "remove_action.hpp"
#include "sprite/order.hpp"
#include "sprite/rotation_type.hpp"
#include "../entity_id.hpp"
#include "../animation_type.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace draw
{

class model
:
	public container
{
public:
	model(
		draw::environment const &,
		entity_id,
		fcppt::string const &name,
		sprite::order,
		bool needs_healthbar,
		draw::remove_action::type
	);

	~model();

	funit max_health() const;
	funit health() const;
protected:
	virtual void
	update(
		time_type
	);

	using container::orientation;

	virtual void
	orientation(
		sprite::rotation_type
	);

	void
	orientation(
		sprite::rotation_type,
		size_type index
	);
	
	bool
	may_be_removed() const;
	
	draw::remove_action::type
	remove_action() const;

	virtual void
	speed(
		vector2 const &
	);

	using container::speed;

	model_part &
	part(
		sprite_part_index const &
	);

	model_part const &
	part(
		sprite_part_index const &
	) const;

	bool dead() const;
	bool walking() const;

	bool has_health() const;

	virtual void on_decay();
private:
	void health(funit);
	void max_health(funit);
	void weapon(weapon_type::type);
	void start_attacking();
	void stop_attacking();
	void start_reloading();
	void stop_reloading();
	void change_animation();
	void change_animation(
		animation_type::type);
	animation_type::type animation() const;
	animation_type::type fallback_anim(
		animation_type::type) const;
	void update_healthbar();
	bool animations_ended() const;

	static fcppt::log::object &
	log();

	bool            attacking,
	                reloading;
	funit           health_,
	                max_health_;
	fcppt::scoped_ptr<
		healthbar
	> healthbar_;

	draw::remove_action::type remove_action_;
	
	typedef boost::ptr_vector<
		model_part
	> part_vector;
	part_vector parts;
};

}
}

#endif
