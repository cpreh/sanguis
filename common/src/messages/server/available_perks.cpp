#include <sanguis/messages/server/available_perks.hpp>
#include <sanguis/messages/server/instantiate_message.hpp>
#include <alda/serialization/load/dynamic_len.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>


SANGUIS_MESSAGES_SERVER_INSTANTIATE_MESSAGE(
	sanguis::messages::server::available_perks
);
