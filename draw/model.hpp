#ifndef SANGUIS_DRAW_MODEL_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_HPP_INCLUDED

#include "model_part.hpp"
#include "sprite.hpp"
#include "healthbar.hpp"
#include "../entity_id.hpp"
#include <sge/sprite/types.hpp>
#include <sge/math/vector.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <vector>

namespace sanguis
{
namespace draw
{

class model : public sprite {
public:
	model(
		entity_id id,
		sge::string const& name);
	sprite_vector to_sprites() const;
protected:	
private:
	void health(sge::space_unit);
	void max_health(sge::space_unit);

	typedef std::vector<model_part> part_vector;
	part_vector parts;
	
	healthbar healthbar_;
};

}
}

#endif
