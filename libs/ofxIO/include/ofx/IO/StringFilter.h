//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <set>
#include <string>
#include <unordered_set>
#include "json.hpp"


namespace ofx {
namespace IO {


/// \brief A filter for strings.
///
/// User-defined blacklists and whitelists are used to remove or replace
/// strings.
class StringFilter
{
public:
    struct Settings;

    StringFilter();
    StringFilter(const Settings& settings);
    ~StringFilter();

    void setup(const Settings& settings);

    /// \returns the Settings.
    Settings settings() const;

    std::string filter(const std::string& input) const;

    std::vector<std::string> getBlacklist() const;
    void setBlacklist(const std::vector<std::string>& list);

    std::vector<std::string> getWhitelist() const;
    void setWhitelist(const std::vector<std::string>& list);

    struct Settings
    {
        char replacement = DEFAULT_REPLACEMENT;
        bool ignoreCase = true;

        const static char DEFAULT_REPLACEMENT;
    };


private:
    /// \brief List of blacklisted strings in UTF8 format.
    std::vector<std::string> _blackList;

    /// \brief List of whitelisted strings in UTF8 format.
    std::vector<std::string> _whitelist;

    /// \brief True if lists need to be rebuilt.
    mutable bool _listDirty = true;

    /// \brief Rebuild lists if needed.
    void _rebuildLists() const;

    /// \brief A list of blacklisted words minus whitelisted words.
    mutable std::vector<std::string> _wordList;

    mutable std::unordered_set<std::string> _wordSet;

    /// \brief A list of blacklisted phrases minutes whitelisted phrases.
    mutable std::vector<std::string> _phraseList;

    /// \brief The current settings.
    Settings _settings;
};



inline void to_json(nlohmann::json& j, const StringFilter& v)
{
    j["settings"]["replacement"] = v.settings().replacement;
    j["settings"]["ignore_case"] = v.settings().ignoreCase;


    j["blacklist"] = v.getBlacklist();
    j["whitelist"] = v.getWhitelist();
}


inline void from_json(const nlohmann::json& j, StringFilter& v)
{
    v.setBlacklist(j.value("blacklist", std::vector<std::string>()));
    v.setWhitelist(j.value("whitelist", std::vector<std::string>()));

    nlohmann::json settings = j.value("settings", nlohmann::json());

    StringFilter::Settings s;

    if (!settings.is_null())
    {
        int c = settings.value("replacement", int(StringFilter::Settings::DEFAULT_REPLACEMENT));
        s.replacement = char(c);
        s.ignoreCase = settings.value("ignore_case", true);
        v.setup(s);
    }
}


} } // namespace ofx::IO
