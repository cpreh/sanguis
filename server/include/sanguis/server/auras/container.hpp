#ifndef SANGUIS_SERVER_AURAS_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_CONTAINER_HPP_INCLUDED

#include <sanguis/server/auras/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::auras
{

using container = std::vector<sanguis::server::auras::unique_ptr>;

}

#endif
