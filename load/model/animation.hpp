#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include "global_parameters_fwd.hpp"
#include "animation_sound_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class animation {
public:
	sge::sprite::animation_series const &
	get() const;

	animation_sound const &
	sounds() const;
private:
	animation(
		global_parameters const &,
		sge::parse::ini::entry_vector const &entries,
		sge::texture::part_ptr);

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
