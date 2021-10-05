#ifndef SANGUIS_MODEL_ANIMATION_DELAY_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_ANIMATION_DELAY_FWD_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace sanguis::model
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	std::chrono::milliseconds,
	animation_delay
);

}

#endif
