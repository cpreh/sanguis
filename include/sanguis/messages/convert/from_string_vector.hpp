#ifndef SANGUIS_MESSAGES_CONVERT_FROM_STRING_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONVERT_FROM_STRING_VECTOR_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sanguis/messages/types/string_vector.hpp>


namespace sanguis
{
namespace messages
{
namespace convert
{

sanguis::string_vector
from_string_vector(
	sanguis::messages::types::string_vector const &
);

}
}
}

#endif
