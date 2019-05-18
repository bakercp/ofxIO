//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <set>
#include <string>
#include <json.hpp>


namespace ofx {
namespace IO {


/// \brief A filter for strings.
///
/// User-defined blacklists and whitelists are used to remove or replace
/// strings.
class StringFilter
{
public:
    enum ReplacementType
    {
        ALL,
        CONSONANTS,
        VOWELS
    };

    StringFilter();
    ~StringFilter();

    /// \brief Replace
    std::string filter(const std::string& input,
                       char32_t replacement = '*',
                       bool ignoreCase = true) const;

    std::vector<std::string> getBlacklist() const;
    void setBlacklist(const std::vector<std::string>& list);

    std::vector<std::string> getWhitelist() const;
    void setWhitelist(const std::vector<std::string>& list);

    std::vector<std::string> getBlacklistRegex() const;
    void setBlacklistRegex(const std::vector<std::string>& list);

    std::vector<std::string> getWhitelistRegex() const;
    void setWhitelistRegex(const std::vector<std::string>& list);

private:
    /// \brief List of blacklisted strings in UTF8 format.
    std::vector<std::string> _blackList;

    /// \brief List of whitelisted strings in UTF8 format.
    std::vector<std::string> _whitelist;

    /// \brief List of blacklisted regex patterns in UTF8 format.
    std::vector<std::string> _blackListRegex;

    /// \brief List of whitelisted regex patterns in UTF8 format.
    std::vector<std::string> _whitelistRegex;

    /// \brief True if lists need to be rebuilt.
    mutable bool _listDirty = true;

    /// \brief Rebuild lists if needed.
    void _rebuildLists() const;

    /// \brief A list of blacklisted words minus whitelisted words.
    mutable std::vector<std::string> _list;

    /// \brief A list of blacklisted regex patterns minus whitelisted regex patterns.
    mutable std::vector<std::string> _listRegex;

};



inline void to_json(nlohmann::json& j, const StringFilter& v)
{
    j["blacklist"] = v.getBlacklist();
    j["blacklist_regex"] = v.getBlacklistRegex();
    j["whitelist"] = v.getWhitelist();
    j["whitelist_regex"] = v.getWhitelistRegex();
}


inline void from_json(const nlohmann::json& j, StringFilter& v)
{
    v.setBlacklist(j.value("blacklist", std::vector<std::string>()));
    v.setBlacklistRegex(j.value("blacklist_regex", std::vector<std::string>()));
    v.setWhitelist(j.value("whitelist", std::vector<std::string>()));
    v.setWhitelistRegex(j.value("whitelist_regex", std::vector<std::string>()));
}


} } // namespace ofx::IO
