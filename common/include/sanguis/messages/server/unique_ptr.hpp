#ifndef SANGUIS_MESSAGES_SERVER_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/message/base_unique_ptr.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
unique_ptr
=
alda::message::base_unique_ptr<
	sanguis::messages::server::types::alda_type
>;

}
}
}

#endif
