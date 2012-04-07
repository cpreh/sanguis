#ifndef SANGUIS_LOAD_MODEL_ANIMATION_OBJECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_OBJECT_HPP_INCLUDED

#include <sanguis/load/model/animation/object_fwd.hpp>
#include <sanguis/load/model/animation/context_fwd.hpp>
#include <sanguis/load/model/animation/context_ptr.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/frame_cache.hpp>
#include <sanguis/load/resource/texture_context.hpp>
#include <sanguis/load/resource/texture_identifier.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
namespace animation
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	model::animation::context_ptr
	load() const;

	~object();

	object(
		sge::parse::json::object const &,
		model::global_parameters const &
	);
private:
	sge::parse::json::object object_;

	model::global_parameters param_;

	mutable frame_cache frame_cache_;

	resource::texture_identifier texture_;

	void
	fill_cache(
		sge::renderer::lock_rect const &
	) const;
};

}
}
}
}

#endif
