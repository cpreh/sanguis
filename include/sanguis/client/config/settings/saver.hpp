#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_SAVER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_SAVER_HPP_INCLUDED

#include <sanguis/client/config/settings/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

class saver
{
	FCPPT_NONCOPYABLE(
		saver
	);
public:
	explicit saver(
		object const &
	);

	~saver();
private:
	settings::object const &object_;
};

}
}
}
}

#endif
