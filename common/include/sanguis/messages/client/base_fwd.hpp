#ifndef SANGUIS_MESSAGES_CLIENT_BASE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_BASE_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/message/base_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

using
base
=
alda::message::base<
	sanguis::messages::client::types::alda_type
>;

}
}
}

#endif
