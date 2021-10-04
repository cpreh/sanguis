#ifndef SANGUIS_MESSAGES_TYPES_STRING_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_STRING_VECTOR_HPP_INCLUDED

#include <sanguis/messages/types/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::messages::types
{

using
string_vector
=
std::vector<
	sanguis::messages::types::string
>;

}

#endif
