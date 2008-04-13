#ifndef SANGUIS_DRAW_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_ENTITY_HPP_INCLUDED

#include <vector>
#include <sge/sprite/object.hpp>
#include <sge/math/vector.hpp>
#include <sge/time.hpp>
#include "../entity_id.hpp"
#include "../weapon_type.hpp"

namespace sanguis
{
namespace draw
{

class entity {
public:
	typedef std::vector<sge::sprite::object> sprite_vector;
	typedef sge::space_unit time_type;

	explicit entity(entity_id id);
	virtual void update(time_type) = 0;
	virtual sprite_vector to_sprites() const = 0;
	entity_id id() const;
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
protected:
	virtual const sge::math::vector2& speed() const = 0;
	virtual sge::space_unit orientation() const = 0;
private:
	entity_id        id_;
};

}
}

#endif
