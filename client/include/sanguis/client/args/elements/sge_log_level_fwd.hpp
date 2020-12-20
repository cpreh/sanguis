#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_SGE_LOG_LEVEL_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_SGE_LOG_LEVEL_FWD_HPP_INCLUDED

#include <sanguis/client/args/labels/sge_log_level.hpp>
#include <fcppt/log/level_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace args
{
namespace elements
{

using
sge_log_level
=
fcppt::record::element<
	sanguis::client::args::labels::sge_log_level,
	fcppt::log::level
>;

}
}
}
}

#endif
