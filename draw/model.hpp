#ifndef SANGUIS_DRAW_MODEL_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_HPP_INCLUDED

#include "model_part.hpp"
#include "sprite.hpp"
#include "healthbar.hpp"
#include "../entity_id.hpp"
#include "../animation_type.hpp"
#include <sge/sprite/types.hpp>
#include <sge/math/vector.hpp>
#include <sge/log/fwd.hpp>
#include <sge/string.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/scoped_ptr.hpp>

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{

class sprite_part_index;

class model : public sprite {
public:
	model(
		load::context const &,
		entity_id id,
		system &,
		sge::string const& name,
		object::order_type order,
		bool needs_healthbar = true,
		funit start_health = static_cast<funit>(0));

	funit max_health() const;
	funit health() const;
protected:
	virtual void update(time_type);
	using sprite::orientation;
	virtual void orientation(
		sge::sprite::rotation_type);
	void orientation(
		sge::sprite::rotation_type,
		sprite_vector::size_type index);
	bool may_be_removed() const;
	virtual void speed(
		vector2 const &);
	using sprite::speed;
	model_part &part(
		sprite_part_index const &);
	model_part const &part(
		sprite_part_index const &) const;
	bool dead() const;
	bool walking() const;
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

	static sge::log::logger &log();

	bool            attacking,
	                reloading;
	funit health_,
	                max_health_;
	boost::scoped_ptr<healthbar> healthbar_;
	
	typedef boost::ptr_vector<
		model_part
	> part_vector;
	part_vector parts;
};

}
}

#endif
