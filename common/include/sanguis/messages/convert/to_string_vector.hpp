#ifndef SANGUIS_MESSAGES_CONVERT_TO_STRING_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONVERT_TO_STRING_VECTOR_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sanguis/common/symbol.hpp>
#include <sanguis/messages/types/string_vector.hpp>


namespace sanguis::messages::convert
{

SANGUIS_COMMON_SYMBOL
sanguis::messages::types::string_vector
to_string_vector(
	sanguis::string_vector const &
);

}

#endif
