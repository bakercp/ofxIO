//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/StringFilter.h"
#include <regex>
#include "ofUtils.h"


namespace ofx {
namespace IO {


StringFilter::StringFilter()
{
}


StringFilter::~StringFilter()
{
}


std::string StringFilter::filter(const std::string& _input,
                                 char32_t replacementChar,
                                 bool ignoreCase) const
{
    _rebuildLists();

    std::string input = _input;

    for (auto& needle: _list)
    {
        std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript;
        if (ignoreCase)
            flags |= std::regex_constants::icase;

        std::regex regexNeedle(needle, flags);
        std::string replacement(ofUTF8Length(needle), replacementChar);
        input = std::regex_replace(input, regexNeedle, replacement);
    }

    for (auto& needle: _listRegex)
    {
        std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript;
        if (ignoreCase)
            flags |= std::regex_constants::icase;

        std::regex regexNeedle(needle, flags);
        std::string replacement(ofUTF8Length(needle), replacementChar);
        input = std::regex_replace(input, regexNeedle, replacement);
    }

    return input;
}


std::vector<std::string> StringFilter::getBlacklist() const
{
    return _blackList;
}


void StringFilter::setBlacklist(const std::vector<std::string>& list)
{
    _blackList = list;
    _listDirty = true;
}


std::vector<std::string> StringFilter::getWhitelist() const
{
    return _whitelist;
}


void StringFilter::setWhitelist(const std::vector<std::string>& list)
{
    _whitelist = list;
    _listDirty = true;
}


std::vector<std::string> StringFilter::getBlacklistRegex() const
{
    return _blackListRegex;
}


void StringFilter::setBlacklistRegex(const std::vector<std::string>& list)
{
    _blackListRegex = list;
    _listDirty = true;
}


std::vector<std::string> StringFilter::getWhitelistRegex() const
{
    return _whitelistRegex;
}


void StringFilter::setWhitelistRegex(const std::vector<std::string>& list)
{
    _whitelistRegex = list;
    _listDirty = true;
}


void StringFilter::_rebuildLists() const
{
    if (_listDirty)
    {
        _list = _blackList;
        for (auto& item: _whitelist)
            _list.erase(std::remove(_list.begin(), _list.end(), item), _list.end());

        // Order list by length to make sure smaller versions of words do not occur first.
        std::sort(_list.begin(), _list.end(), [](const std::string& a, const std::string& b) { return a.size() > b.size(); });

        _listRegex = _blackListRegex;
        for (auto& item: _whitelistRegex)
            _listRegex.erase(std::remove(_listRegex.begin(), _listRegex.end(), item), _listRegex.end());

        // Order list by length to make sure smaller versions of words do not occur first.
        std::sort(_listRegex.begin(), _listRegex.end(), [](const std::string& a, const std::string& b) { return a.size() > b.size(); });

        _listDirty = false;
    }
}




} }  // namespace ofx::IO
