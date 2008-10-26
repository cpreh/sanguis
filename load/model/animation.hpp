#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sge/path.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class animation_sound;

class animation {
public:
	sge::sprite::animation_series const &get() const;
	animation_sound const &sounds() const;
private:
	explicit animation(
		sge::path const &);

	friend class weapon_category;

	sge::path path;
	mutable sge::shared_ptr<
		sge::sprite::animation_series
	> anim;

	mutable sge::shared_ptr<
		animation_sound
	> sounds_;
};

}
}
}

#endif
