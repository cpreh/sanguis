#ifndef SANGUIS_DRAW_MODEL_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_HPP_INCLUDED

#include "sprite.hpp"
#include "healthbar.hpp"
#include "remove_action.hpp"
#include "../entity_id.hpp"
#include "../animation_type.hpp"
#include <sge/log/fwd.hpp>
#include <sge/string.hpp>
#include <sge/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace draw
{

class sprite_part_index;
class model_part;
class environment;

class model : public sprite {
public:
	model(
		draw::environment const &,
		entity_id id,
		sge::string const &name,
		sge::sprite::intrusive_order order,
		bool needs_healthbar,
		draw::remove_action::type);
	~model();

	funit max_health() const;
	funit health() const;
protected:
	virtual void update(time_type);
	using sprite::orientation;
	virtual void orientation(
		sge::sprite::rotation_type);
	void orientation(
		sge::sprite::rotation_type,
		size_type index);
	
	bool may_be_removed() const;
	
	draw::remove_action::type
	remove_action() const;

	virtual void speed(
		vector2 const &);
	using sprite::speed;
	model_part &part(
		sprite_part_index const &);
	model_part const &part(
		sprite_part_index const &) const;
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

	static sge::log::logger &log();

	bool            attacking,
	                reloading;
	funit           health_,
	                max_health_;
	sge::scoped_ptr<
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
