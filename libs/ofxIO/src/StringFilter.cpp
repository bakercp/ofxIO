//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/StringFilter.h"
#include "ofUtils.h"


namespace ofx {
namespace IO {


const char StringFilter::Settings::DEFAULT_REPLACEMENT = '*';


StringFilter::StringFilter()
{
}


StringFilter::StringFilter(const Settings& settings):
    _listDirty(true),
    _settings(settings)
{
}


StringFilter::~StringFilter()
{
}


void StringFilter::setup(const Settings& settings)
{
    _listDirty = true;
    _settings = settings;
}


StringFilter::Settings StringFilter::settings() const
{
    return _settings;
}

    
std::string StringFilter::filter(const std::string& _input) const
{
    _rebuildLists();

    std::string output = _input;
    std::string input = _input;

    if (_settings.ignoreCase)
        std::transform(input.begin(),
                       input.end(),
                       input.begin(),
                       ::tolower);

    // Remove whole phrases.
    for (auto needle: _phraseList)
    {
        if (needle.size() <= input.size())
        {
            std::size_t pos = input.find(needle);
            while (pos != std::string::npos)
            {
                std::string replacement = needle;

                std::transform(replacement.begin(),
                               replacement.end(),
                               replacement.begin(),
                               [&](unsigned char c) -> unsigned char
                {
                    return std::isspace(c) ? c : _settings.replacement;
                });

                output.replace(pos, needle.size(), replacement);
                pos = input.substr(pos + needle.size()).find(needle);
            }
        }
    }

    // Remove individual words.
    std::string result;
    std::size_t currentWordStartIndex = std::numeric_limits<std::size_t>::max();
    std::size_t lastDelimiter = std::numeric_limits<std::size_t>::max();

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        bool isDelimiter = std::isspace(input[i])
                        || std::ispunct(input[i]);

        bool wordEnd = false;

        if (i == 0)
        {
            if (isDelimiter)
                lastDelimiter = i;
            else
                currentWordStartIndex = i;
        }
        else if (isDelimiter)
        {
            if (lastDelimiter != i - 1)
                wordEnd = true;

            lastDelimiter = i;
        }
        else // not a delimiter or i == 0
        {
            if (lastDelimiter == i - 1)
                currentWordStartIndex = i;
            else if (i == input.size() - 1)
                wordEnd = true;
        }

        if (wordEnd)
        {
            std::size_t size = i - currentWordStartIndex;
            std::string word = input.substr(currentWordStartIndex, size);

            for (auto& needle: _wordList)
            {
                if (needle.size() == size)
                {
                    if (_settings.ignoreCase)
                        std::transform(word.begin(),
                                       word.end(),
                                       word.begin(),
                                       ::tolower);

                    if (_wordSet.find(word) != _wordSet.end())
                    {
                        std::string replacement(size, _settings.replacement);
                        output.replace(currentWordStartIndex, size, replacement);
                    }
                }
                if (needle.size() < size) break;
            }
        }
    }

    return output;
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


void StringFilter::_rebuildLists() const
{
    auto hasWhitespace = [](const std::string& input) -> bool
    {
        for (auto& c: input)
            if (std::isspace(c))
                return true;

        return false;
    };

    if (_listDirty)
    {
        _wordList.clear();
        _phraseList.clear();

        for (auto item: _blackList)
        {
            if (_settings.ignoreCase)
                std::transform(item.begin(),
                               item.end(),
                               item.begin(),
                               ::tolower);

            if (hasWhitespace(item))
                _phraseList.push_back(item);
            else _wordList.push_back(item);
        }

        for (auto item: _whitelist)
        {
            if (_settings.ignoreCase)
                std::transform(item.begin(),
                               item.end(),
                               item.begin(),
                               ::tolower);

            if (hasWhitespace(item))
                _phraseList.erase(std::remove(_phraseList.begin(),
                                              _phraseList.end(),
                                              item),
                                  _phraseList.end());
            else
                _wordList.erase(std::remove(_wordList.begin(),
                                            _wordList.end(),
                                            item),
                                _wordList.end());
        }

        auto sortBySize = [](const std::string& a,
                             const std::string& b) -> bool
        {
            return a.size() > b.size();
        };

        // Order list by length to make sure smaller versions of words do not occur first.
        std::sort(_phraseList.begin(), _phraseList.end(), sortBySize);
        std::sort(_wordList.begin(), _wordList.end(), sortBySize);

        _wordSet = std::unordered_set<std::string>(_wordList.begin(), _wordList.end());

        _listDirty = false;
    }
}


} }  // namespace ofx::IO
