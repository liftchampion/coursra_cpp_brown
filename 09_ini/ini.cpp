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

	void parse_section(istream& input, Document& doc) {
		string str;
		getline(input, str);

		string_view sv(str);
		if (*sv.begin() == '[') { sv = sv.substr(1); }
		if (!sv.empty() && *(sv.end() - 1) == ']') { sv = sv.substr(0,sv.length() - 1); }

		string name(sv);

		//cout << name << endl;

		Section* section = &doc.AddSection(name);

		for (getline(input, str); input.peek() != '[' && input; getline(input, str)) {
			if (str.empty()) { continue; }
			auto delim_iter = str.find('=');
			if (delim_iter != string::npos) {
				string key(str.begin(), str.begin() + delim_iter);
				string val(str.begin() + delim_iter + 1, str.end());
				section->insert({move(key), move(val)});
			} else {
				section->insert({str, ""});
			}


			//cout << "    " << ins.first->first << " " << ins.first->second << endl;
		}
		//cout << endl;
	}

	Document Load(istream& input) {
		Document doc;
		char c;

		while (input && input.peek() != '[') { input >> c; }


		for (; input; parse_section(input, doc)) {}

		return doc;
	}

}