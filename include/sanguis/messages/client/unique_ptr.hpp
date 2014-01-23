#ifndef SANGUIS_MESSAGES_CLIENT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/message/base_unique_ptr.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::base_unique_ptr<
	sanguis::messages::client::types::alda_type
>
unique_ptr;

}
}
}

#endif
