#ifndef SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/client/load/model/animation_fwd.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sanguis/model/animation_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
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
		sanguis::model::animation const &,
		sanguis::client::load::model::global_parameters const &
	);

	~animation();

	sanguis::client::load::resource::animation::series const &
	series() const;

	sanguis::client::load::resource::optional_sound const &
	sound() const;
private:
	sge::texture::part const &texture_;

	sanguis::client::load::resource::animation::series const series_;

	sanguis::client::load::resource::optional_sound const sound_;
};

}
}
}
}

#endif
