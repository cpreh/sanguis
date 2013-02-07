#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/load/model/animation_fwd.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

class animation
{
	FCPPT_NONCOPYABLE(
		animation
	);
public:
	animation(
		sge::parse::json::object const &,
		sanguis::load::model::global_parameters const &
	);

	~animation();

	sanguis::load::resource::animation::series const &
	series() const;
private:
	sge::texture::const_part_shared_ptr const texture_;

	sanguis::load::resource::animation::series const series_;
};

}
}
}

#endif
