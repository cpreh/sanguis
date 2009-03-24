#ifndef SANGUIS_LOAD_PARTICLE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_ANIMATIONS_HPP_INCLUDED

#include "animation_fwd.hpp"
#include "random_animation_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include "animation_container.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace particle
{
class animations {
	SGE_NONCOPYABLE(animations)
public:
	random_animation const &
	random() const;

	animations(
		sge::filesystem::path const &,
		resource::context const &);
	~animations();

	void preload() const;
private:
	animation_container animations_;

	sge::scoped_ptr<
		random_animation
	> random_animation_;
};

}
}
}

#endif
