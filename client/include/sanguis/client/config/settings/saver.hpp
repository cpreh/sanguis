#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_SAVER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_SAVER_HPP_INCLUDED

#include <sanguis/client/config/settings/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::client::config::settings
{

class saver
{
	FCPPT_NONMOVABLE(
		saver
	);
public:
	explicit
	saver(
		fcppt::reference<
			sanguis::client::config::settings::object const
		>
	);

	~saver();
private:
	fcppt::reference<
		sanguis::client::config::settings::object const
	> const object_;
};

}

#endif
