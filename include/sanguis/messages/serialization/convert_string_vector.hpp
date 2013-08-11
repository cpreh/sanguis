#ifndef SANGUIS_MESSAGES_SERIALIZATION_CONVERT_STRING_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_CONVERT_STRING_VECTOR_HPP_INCLUDED

#include <sanguis/messages/types/string_vector.hpp>
#include <sanguis/string_vector.hpp>


namespace sanguis
{
namespace messages
{
namespace serialization
{

messages::types::string_vector
convert_string_vector(
	sanguis::string_vector const &
);

sanguis::string_vector
convert_string_vector(
	messages::types::string_vector const &
);

}
}
}

#endif
