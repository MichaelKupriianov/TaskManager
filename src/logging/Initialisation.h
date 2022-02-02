#pragma once

#include <string>
#include <boost/log/trivial.hpp>

void InitialisationLoggingToConsole(const boost::log::trivial::severity_level& severity);

void InitialisationLoggingToFile(const std::string& filename, const boost::log::trivial::severity_level& severity);