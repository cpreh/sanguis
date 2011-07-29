#ifndef SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "../frame_cache_fwd.hpp"
#include "../../resource/animation/series.hpp"
#include "../../resource/texture_context.hpp"
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
namespace animation
{

class context
{
	FCPPT_NONASSIGNABLE(
		context
	);
public:
	typedef fcppt::function::object<
		void (
			sge::renderer::lock_rect const &
		)
	> cache_callback;

	context(
		resource::texture_context const &,
		frame_cache const &,
		cache_callback const &
	);

	~context();

	void
	update();

	bool
	is_finished() const;

	resource::animation::series const &
	result() const;
private:
	resource::texture_context texture_context_;

	frame_cache const &frame_cache_;

	cache_callback cache_callback_;

	bool is_finished_;

	resource::animation::series animation_;
};

}
}
}
}

#endif
