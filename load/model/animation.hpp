#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include "global_parameters.hpp"
#include "animation_sound_fwd.hpp"
#include "../resource/texture_context_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member.hpp>
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

	bool update();
private:
	animation(
		sge::parse::json::object const &,
		global_parameters const &);

	friend class weapon_category;

	global_parameters param_;
	sge::parse::json::member_vector members_;

	load::resource::texture_context_ptr 
		context_;

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
