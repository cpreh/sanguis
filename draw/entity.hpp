#ifndef SANGUIS_DRAW_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_ENTITY_HPP_INCLUDED

#include "types.hpp"
#include "../entity_id.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../diff_clock.hpp"
#include <sge/math/vector.hpp>
#include <sge/time/timer.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace sanguis
{
namespace draw
{

class entity : boost::noncopyable {
public:
	typedef std::vector<
		object> sprite_vector;

	virtual void update(time_type);
	entity_id id() const;
	void decay();
	void decay_time(
		time_type);
	bool may_be_removed() const;
	virtual void orientation(sge::sprite::rotation_type) = 0;
	virtual void speed(const sge::math::vector2&) = 0;
	virtual void pos(const sge::sprite::point&) = 0;
	virtual void dim(const sge::sprite::dim&) = 0;
	virtual void visible(bool) = 0;
	virtual void health(sge::space_unit);
	virtual void max_health(sge::space_unit);
	virtual void weapon(weapon_type::type);
	virtual void start_attacking();
	virtual void stop_attacking();
	virtual ~entity();
protected:
	entity(
		entity_id id,
		system &);
	virtual const sge::math::vector2& speed() const = 0;
	virtual sge::space_unit orientation() const = 0;

	system &get_system();
private:
	entity_id        id_;
	system          &sys;
	diff_clock       diff_clock_;
	sge::time::timer decay_timer;
};

}
}

#endif
