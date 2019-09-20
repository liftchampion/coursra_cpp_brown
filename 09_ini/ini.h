/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 15:52:24 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/20 15:52:24 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_map>

using namespace std;

namespace Ini {
	using Section = unordered_map<string, string>;

	class Document {
	public:
		Section& AddSection(string name);
		const Section& GetSection(const string& name) const;
		size_t SectionCount() const;

	private:
		unordered_map<string, Section> sections;
	};

	Document Load(istream& input);
}
