#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sge/filesystem/path.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/parse/ini/entry_vector.hpp>
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
		sge::texture::part_ptr,
		sge::renderer::dim_type const &cell_size,
		sge::parse::ini::entry_vector const &entries);

	friend class weapon_category;

	sge::shared_ptr<
		sge::sprite::animation_series
	> anim;

	sge::shared_ptr<
		animation_sound
	> sounds_;
};

}
}
}

#endif
