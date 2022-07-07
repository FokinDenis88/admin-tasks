#include "general.hpp"

#include <regex>
//#include <utility>    // for std::move()

namespace admin_tasks {
    /// Get List of values, when one ini value consists list of values separated by char '|'
    std::list<std::wstring> GetIniValuesList(const std::wstring& ini_values) {
        std::list<std::wstring> values_list{};

        // "[^\|]+(?=\|)|(?<=\|)[^\|]+(?=\z)"
        std::wregex pattern{ L"[^\\|]+(?=\\|)|(?<=\\|)[^\\|]+(?=\\z)" };
        std::wsregex_iterator begin(ini_values.begin(), ini_values.end(), pattern);
        const std::wsregex_iterator end = std::wsregex_iterator();
        for (std::wsregex_iterator i = begin; i != end; ++i) {
            values_list.push_back(i->str());
        }

        return values_list;
    }
    // "(?<separator>\|)(?<value>[^\k<separator>]+)(?=\k<separator>)|(?<=\k<separator>)\k<value>(?=\z)"
    // "(?<value>[^\|]+)(?=\|)|(?<=\|)\k<value>(?=\z)"

} // !namespace admin_tasks
