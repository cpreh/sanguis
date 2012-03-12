#ifndef SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_AUTO_PTR_HPP_INCLUDED

#include <sanguis/messages/types/alda_type.hpp>
#include <alda/message/base_unique_ptr.hpp>


namespace sanguis
{
namespace messages
{

typedef alda::message::base_unique_ptr<
	sanguis::messages::types::alda_type
>::type auto_ptr;

}
}

#endif
