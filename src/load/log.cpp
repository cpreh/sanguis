#include "log.hpp"
#include "../log_location.hpp"
#include "../log_parameters.hpp"
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::load::log,
	sanguis::log_parameters(
		sanguis::log_location()
		/
		FCPPT_TEXT("load")
	)
)
