#ifndef SANGUIS_LOAD_MODEL_MAKE_SERIES_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_SERIES_HPP_INCLUDED

#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/resource/animation/series_fwd.hpp>
#include <sanguis/model/animation_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::resource::animation::series
make_series(
	sanguis::model::animation const &,
	sanguis::load::model::global_parameters const &,
	sge::texture::part const &
);

}
}
}

#endif
