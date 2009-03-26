#ifndef SANGUIS_CLIENT_TO_PERK_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_TO_PERK_TYPE_HPP_INCLUDED

#include "../perk_type.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace client
{

perk_type::type
to_perk_type(
	sge::string const &);

}
}

#endif
