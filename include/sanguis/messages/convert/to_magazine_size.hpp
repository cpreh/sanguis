#ifndef SANGUIS_MESSAGES_CONVERT_TO_MAGAZINE_SIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONVERT_TO_MAGAZINE_SIZE_HPP_INCLUDED

#include <sanguis/magazine_type.hpp>
#include <sanguis/messages/types/magazine_size.hpp>


namespace sanguis
{
namespace messages
{
namespace convert
{

sanguis::messages::types::magazine_size
to_magazine_size(
	sanguis::magazine_type
);

}
}
}

#endif
