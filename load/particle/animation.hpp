#ifndef SANGUIS_LOAD_PARTICLE_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_ANIMATION_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include <sge/sprite/animation_series_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace particle
{

class animation {
	SGE_NONCOPYABLE(animation)
public:
	sge::sprite::animation_series const &
	get() const;

	animation(
		sge::filesystem::path const &,
		resource::context const &);
	~animation();
private:
	sge::filesystem::path const path;
	resource::context const &ctx;

	mutable sge::scoped_ptr<
		sge::sprite::animation_series
	> anim;
};

}
}
}

#endif
