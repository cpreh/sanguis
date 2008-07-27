#ifndef SANGUIS_DRAW_MODEL_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_HPP_INCLUDED

#include "model_part.hpp"
#include "sprite.hpp"
#include "healthbar.hpp"
#include "../entity_id.hpp"
#include "../animation_type.hpp"
#include <sge/sprite/types.hpp>
#include <sge/math/vector.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace draw
{

class model : public sprite {
public:
	model(
		entity_id id,
		system &,
		sge::string const& name);
protected:
	virtual void update(time_type);
	virtual void orientation(
		sge::sprite::rotation_type);
	void orientation(
		sge::sprite::rotation_type,
		sprite_vector::size_type index);

	sge::space_unit max_health() const;
	sge::space_unit health() const;
private:
	void health(sge::space_unit);
	void max_health(sge::space_unit);
	void weapon(weapon_type::type);
	void start_attacking();
	void stop_attacking();
	animation_type::type animation() const;

	bool attacking;
	healthbar healthbar_;
	
	typedef boost::ptr_vector<model_part> part_vector;
	part_vector parts;
};

}
}

#endif
