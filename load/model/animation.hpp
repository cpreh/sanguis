#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include "global_parameters.hpp"
#include "frame_cache.hpp"
#include "animation_sound_fwd.hpp"
#include "../resource/texture_context.hpp"
#include "../resource/texture_identifier.hpp"
#include "../resource/context_fwd.hpp"
#include "animation_context_fwd.hpp"
#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class animation {
public:
	typedef sge::auto_ptr<animation_context> context_ptr;

	animation_sound const &
	sounds() const;

	context_ptr load() const;
private:
	animation(
		sge::parse::json::object const &,
		global_parameters const &);

	friend class weapon_category;

	sge::parse::json::object object_;
	global_parameters param_;

	sge::shared_ptr<
		animation_sound
	> sounds_;

	mutable frame_cache frame_cache_;
	resource::texture_identifier texture_;

	void fill_cache(
		sge::renderer::lock_rect const &) const;
};

}
}
}

#endif
