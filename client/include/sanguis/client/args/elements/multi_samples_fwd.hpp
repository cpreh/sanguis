#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_MULTI_SAMPLES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_MULTI_SAMPLES_FWD_HPP_INCLUDED

#include <sanguis/client/args/labels/multi_samples.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis::client::args::elements
{

using
multi_samples
=
fcppt::record::element<
	sanguis::client::args::labels::multi_samples,
	sge::renderer::pixel_format::optional_multi_samples
>;

}

#endif
