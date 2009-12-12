#include "environment.hpp"

sanguis::draw::environment::environment(
	insert_callback const &insert_,
	load::context const &context_,
	sprite::colored::system &colored_system_,
	sprite::normal::system &normal_system_,
	sprite::client::system &client_system_,
	sprite::particle::system &particle_system_
)
:
	insert_(insert_),
	context_(context_),
	colored_system_(colored_system_),
	normal_system_(normal_system_),
	client_system_(client_system_),
	particle_system_(particle_system_)
{}
	
sanguis::draw::insert_callback const &
sanguis::draw::environment::insert() const
{
	return insert_;
}

sanguis::load::context const &
sanguis::draw::environment::context() const
{
	return context_;
}

sanguis::draw::sprite::colored::system &
sanguis::draw::environment::colored_system() const
{
	return colored_system_;
}

sanguis::draw::sprite::normal::system &
sanguis::draw::environment::normal_system() const
{
	return normal_system_;
}

sanguis::draw::sprite::client::system &
sanguis::draw::environment::client_system() const
{
	return client_system_;
}

sanguis::draw::sprite::particle::system &
sanguis::draw::environment::particle_system() const
{
	return particle_system_;
}
