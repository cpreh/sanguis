#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sge/filesystem/path.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class context;
}
namespace model
{

class animation_sound;

class animation {
public:
	sge::sprite::animation_series const &
	get() const;

	animation_sound const &
	sounds() const;
private:
	animation(
		sge::filesystem::path const &,
		resource::context const &);

	friend class weapon_category;

	sge::filesystem::path path;
	resource::context const &ctx;

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
