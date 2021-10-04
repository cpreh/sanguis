#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED

#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sge/parse/ini/start.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::config::settings
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		fcppt::log::context_reference,
		std::filesystem::path &&
	);

	~object();

	[[nodiscard]]
	sge::parse::ini::start &
	sections();

	[[nodiscard]]
	sge::parse::ini::start const &
	sections() const;

	void
	save() const;

	[[nodiscard]]
	fcppt::log::object &
	log() const;
private:
	mutable fcppt::log::object log_;

	std::filesystem::path const path_;

	sge::parse::ini::start start_;
};

}

#endif
