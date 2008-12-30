#ifndef SANGUIS_DRAW_EXPLOSION_HPP_INCLUDED
#define SANGUIS_DRAW_EXPLOSION_HPP_INCLUDED

#include "entity.hpp"
#include "particle/base_ptr.hpp"
#include "particle/container.hpp"
#include "particle/property_map.hpp"
#include "../particle_type.hpp"
#include <sge/sprite/point.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{
class properties;
}

class environment;

class explosion : public entity {
public:
	explosion(
		draw::environment const &,
		sge::sprite::point const &pos);
	~explosion();
private:
	void update(
		time_type);

	particle::base_ptr
	generate_explosion();

	particle::base_ptr
	generate_particle(
		particle_type::type);

	particle::properties const &
	properties(
		particle_type::type const t) const;
	
	bool may_be_removed() const;

	particle::container particles;
	particle::property_map properties_;
};

}
}

#endif