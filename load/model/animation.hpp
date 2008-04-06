#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sge/path.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <boost/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class animation {
public:
	explicit animation(sge::path const&);
	sge::sprite::texture_animation const& get() const;
private:
	sge::path path;
	boost::shared_ptr<sge::sprite::texture_animation> anim;
};

}
}
}

#endif
