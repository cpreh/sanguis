#ifndef SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_HPP_INCLUDED

#include "animation_context_fwd.hpp"
#include "frame_cache_fwd.hpp"
#include "../resource/texture_context.hpp"
#include <sge/sprite/animation/series.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
class animation_context
{
	FCPPT_NONASSIGNABLE(
		animation_context
	)
public:
	typedef fcppt::function::object<
		void (
			sge::renderer::lock_rect const &
		)
	> cache_callback;

	animation_context(
		resource::texture_context const &,
		frame_cache const &,
		cache_callback const &);
	void update();

	bool is_finished() const;

	sge::sprite::animation::series const &
	result() const;
private:
	resource::texture_context texture_context_;
	frame_cache const &frame_cache_;
	cache_callback cache_callback_;
	bool is_finished_;
	sge::sprite::animation::series animation_;
};
}
}
}

#endif
