#ifndef SANGUIS_DRAW_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_ENTITY_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "system_fwd.hpp"
#include "vector2.hpp"
#include "remove_action.hpp"
#include "sprite/rotation_type.hpp"
#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "../entity_id.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include <sge/log/object_fwd.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace draw
{

class entity {
	SGE_NONCOPYABLE(entity)
public:
	virtual void update(time_type) = 0;
	entity_id id() const;
	void decay();

	virtual bool may_be_removed() const;
	
	virtual draw::remove_action::type
	remove_action() const;

	virtual void on_remove();
	virtual void orientation(sprite::rotation_type);
	virtual void speed(vector2 const &);
	virtual void pos(sprite::point const &);
	virtual void dim(sprite::dim const &);
	virtual void visible(bool);
	virtual void health(funit);
	virtual void max_health(funit);
	virtual void weapon(weapon_type::type);
	virtual void start_attacking();
	virtual void stop_attacking();
	virtual void start_reloading();
	virtual void stop_reloading();

	virtual ~entity();
protected:
	entity(
		draw::environment const &,
		entity_id id);
	
	virtual vector2 const
	speed() const;

	virtual funit
	orientation() const;

	draw::environment const &
	environment() const;

	draw::system &
	system();
private:
	virtual void on_decay();

	static sge::log::object &
	log();

	draw::environment const &env_;
	entity_id               id_;
	bool                    may_be_removed_;
};

}
}

#endif
