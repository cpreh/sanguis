#ifndef SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/client/load/model/animation_fwd.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sanguis/model/animation_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>


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
	FCPPT_NONMOVABLE(
		animation
	);
public:
	animation(
		fcppt::log::object &, // NOLINT(google-runtime-references)
		sanguis::model::animation const &,
		sanguis::client::load::model::global_parameters const &
	);

	~animation();

	[[nodiscard]]
	sanguis::client::load::resource::animation::series const &
	series() const;

	[[nodiscard]]
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
