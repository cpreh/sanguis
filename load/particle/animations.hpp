#ifndef SANGUIS_LOAD_PARTICLE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_ANIMATIONS_HPP_INCLUDED

#include "animation_container.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

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

class animation;
class random_animation;

class animations : boost::noncopyable {
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
