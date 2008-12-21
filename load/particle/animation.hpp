#ifndef SANGUIS_LOAD_PARTICLE_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_ANIMATION_HPP_INCLUDED

#include <sge/sprite/animation_series.hpp>
#include <sge/path.hpp>
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class context;
}
namespace particle
{

class animation {
public:
	animation(
		sge::path const &,
		resource::context const &);

	sge::sprite::animation_series const &
	get() const;
private:
	sge::path const path;
	resource::context const &ctx;

	mutable sge::shared_ptr<
		sge::sprite::animation_series
	> anim;
};

}
}
}

#endif
