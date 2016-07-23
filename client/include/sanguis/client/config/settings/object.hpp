#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED

#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sge/parse/ini/start.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::context &,
		boost::filesystem::path const &
	);

	~object();

	sge::parse::ini::start &
	sections();

	sge::parse::ini::start const &
	sections() const;

	void
	save() const;

	fcppt::log::object &
	log() const;
private:
	mutable fcppt::log::object log_;

	boost::filesystem::path const path_;

	sge::parse::ini::start start_;
};

}
}
}
}

#endif
