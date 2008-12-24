#ifndef SANGUIS_LOAD_PARTICLE_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_ANIMATION_HPP_INCLUDED

#include <sge/sprite/animation_series_fwd.hpp>
#include <sge/path.hpp>
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

class animation : boost::noncopyable {
public:
	sge::sprite::animation_series const &
	get() const;

	animation(
		sge::path const &,
		resource::context const &);
	~animation();
private:
	sge::path const path;
	resource::context const &ctx;

	mutable sge::scoped_ptr<
		sge::sprite::animation_series
	> anim;
};

}
}
}

#endif
