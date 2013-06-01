#ifndef SANGUIS_PIXELS_PER_METER_HPP_INCLUDED
#define SANGUIS_PIXELS_PER_METER_HPP_INCLUDED

#include <sanguis/unsigned_scale.hpp>
#include <fcppt/preprocessor/pure.hpp>


namespace sanguis
{

// TODO: this should be moved when the server knowns how big its objects are
// in terms of non pixel units!
sanguis::unsigned_scale
pixels_per_meter()
FCPPT_PP_PURE;

}

#endif
