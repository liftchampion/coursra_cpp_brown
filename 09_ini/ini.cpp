/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:15:30 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/20 17:15:30 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "ini.h"

using namespace std;

namespace Ini {

	Section& Document::AddSection(string name) {
		return sections[move(name)];
	}
	const Section& Document::GetSection(const string& name) const {
		return sections.at(name);
	}
	size_t Document::SectionCount() const {
		return sections.size();
	}

	inline string get_name(const string& str) {
		string_view sv(str);
		sv = sv.substr(1);
		if (!sv.empty() && *(sv.end() - 1) == ']') {
			sv = sv.substr(0,sv.length() - 1);
		}
		return string(sv);
	}

	Document Load(istream& input) {
		Document doc;
		string str;
		Section* section = nullptr;

		while (getline(input, str)) {
			if (str.empty()) { continue; }
			if (str[0] == '[') {
				section = &doc.AddSection(get_name(str));
				continue;
			}
			if (section) {
				auto delim_pos = str.find('=');
				if (delim_pos != string::npos) {
					string key(str.begin(), str.begin() + delim_pos);
					string val(str.begin() + delim_pos + 1, str.end());
					section->insert({move(key), move(val)});
				} else {
					section->insert({str, ""});
				}
			}
		}
		return doc;
	}
}