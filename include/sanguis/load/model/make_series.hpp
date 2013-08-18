#ifndef SANGUIS_LOAD_MODEL_MAKE_SERIES_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_SERIES_HPP_INCLUDED

#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/resource/animation/series_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::resource::animation::series
make_series(
	sge::parse::json::object const &,
	sanguis::load::model::global_parameters const &,
	sge::texture::part const &
);

}
}
}

#endif
