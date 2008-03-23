#ifndef SANGUIS_TRUNCATION_CHECK_CAST_HPP_INCLUDED
#define SANGUIS_TRUNCATION_CHECK_CAST_HPP_INCLUDED

namespace sanguis
{

template<typename Dest, typename Source>
Dest truncation_check_cast(const Source&);

}

#include "detail/truncation_check_cast_impl.hpp"

#endif
