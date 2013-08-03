#ifndef SANGUIS_MESSAGES_BASE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_BASE_FWD_HPP_INCLUDED

#include <sanguis/messages/types/alda_type.hpp>
#include <alda/message/base_fwd.hpp>


namespace sanguis
{
namespace messages
{

typedef
alda::message::base<
	sanguis::messages::types::alda_type
>
base;

}
}

#endif
