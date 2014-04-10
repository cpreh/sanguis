#include <sanguis/messages/client/console_command.hpp>
#include <sanguis/messages/client/instantiate_message.hpp>
#include <alda/serialization/load/dynamic_len.hpp>
#include <alda/serialization/load/static_size.hpp>


SANGUIS_MESSAGES_CLIENT_INSTANTIATE_MESSAGE(
	sanguis::messages::client::console_command
);
