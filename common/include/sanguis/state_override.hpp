#ifndef SANGUIS_STATE_OVERRIDE_HPP_INCLUDED
#define SANGUIS_STATE_OVERRIDE_HPP_INCLUDED

#include <fcppt/config/compiler.hpp>


#if defined(FCPPT_CONFIG_MSVC_COMPILER)
#define SANGUIS_STATE_OVERRIDE
#else
#define SANGUIS_STATE_OVERRIDE override
#endif

#endif
