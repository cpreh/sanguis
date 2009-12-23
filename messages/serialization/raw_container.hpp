#ifndef SANGUIS_MESSAGES_SERIALIZATION_RAW_CONTAINER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_RAW_CONTAINER_HPP_INCLUDED

#include <fcppt/container/raw_vector_fwd.hpp>
#include <majutsu/raw_data.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

typedef fcppt::container::raw_vector<
	majutsu::raw_data
> raw_container;

}
}
}

#endif
