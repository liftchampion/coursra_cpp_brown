/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prority_container.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 22:40:25 by ggerardy          #+#    #+#             */
/*   Updated: 2019/06/23 22:40:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_runner.h"
#include "profile.h"
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
	using Id = unsigned long long int;
	PriorityCollection() :
			last_id(0), init_prior(0)
	{}
	///[[nodiscard]]
	Id Add(T object) {
		Id id = ++last_id;
		id_to_obj[id] = move(object);
		sorted_info.insert(IdPrior(id, init_prior));
		id_to_prior[id] = init_prior;
		return id;
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
			 IdOutputIt ids_begin) {
		for (auto it = range_begin; it != range_end; ++it) {
			*ids_begin++ = Add(move(*it));
		}
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	///[[nodiscard]]
	bool IsValid(Id id) const {
		return id_to_obj.find(id) != id_to_obj.end();
	}

	// Получить объект по идентификатору
	///[[nodiscard]]
	const T& Get(Id id) const {
		const T& obj_lnk = id_to_obj.at(id);
		return obj_lnk;
	}

	// Увеличить приоритет объекта на 1
	void Promote(Id id) {
		const int prior = id_to_prior[id];
		sorted_info.erase({id, prior});
		sorted_info.insert({id, prior + 1});
		++id_to_prior[id];
	}

	// Получить объект с максимальным приоритетом и его приоритет
	///[[nodiscard]]
	pair<const T&, int> GetMax() const {
		const IdPrior desc = *(prev(sorted_info.end()));
		const T& obj_lnk = id_to_obj.at(desc.id);

		return pair<const T&, int>(obj_lnk, desc.prior);
	}

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, int> PopMax() {
		const IdPrior desc = *(prev(sorted_info.end()));
		T obj = move(id_to_obj.at(desc.id));
		sorted_info.erase(desc);
		id_to_prior.erase(desc.id);
		id_to_obj.erase(desc.id);
		return pair<T, int>(move(obj), desc.prior);
	}

private:
	class IdPrior{
	public:
		IdPrior(Id id, int prior) :
				id(id), prior(prior)
		{}
		bool operator< (const IdPrior& rhs) const {
			if (this->prior < rhs.prior)
				return true;
			if (this->prior == rhs.prior)
				return this->id < rhs.id;
			return false;
		}
		int	prior = 0;
		Id	id = 0;
	};

	set<IdPrior> sorted_info;
	map<Id, int> id_to_prior;
	map<Id, T> id_to_obj;
	Id last_id;
	const int init_prior;
};



class StringNonCopyable : public string {
public:
	using string::string;  // Позволяет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");


	PriorityCollection<string> strings2;
	vector<string> strs = {"hello", "brave", "world"};
	vector<size_t> ids;

	strings2.Add(strs.begin(), strs.end(), back_inserter(ids));


	for (auto id : ids) {
		cout << id << " ";
	}
	cout << endl;
	for (auto id : ids) {
		cout << strings2.Get(id) << " ";
	}
	cout << endl;
	cout << strings2.Get(1) <<  endl;
	cout << strings2.Get(2) <<  endl;
	cout << strings2.Get(3) <<  endl;

	cout << strings.Get(red_id) << endl;
	cout << strings.IsValid(red_id) << endl;
	cout << strings.IsValid(6u) << endl;

	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	cout << "~~~1~~~" << endl;
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	cout << "~~~2~~~" << endl;
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "");
		ASSERT_EQUAL(item.second, 0);
	}
	cout << "~~~3~~~" << endl;
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);

	PriorityCollection<int> strings;
	{
		LOG_DURATION("add 500000");
		for (int i = 0; i < 500000; i++) {
			strings.Add(i);
		}
	}
	{
		LOG_DURATION("pop 500000");
		for (int i = 0; i < 500000; i++) {
			strings.PopMax();
		}
	}

	{
		LOG_DURATION("pop bottom total");
		PriorityCollection<int> strings;
		auto hello_id = strings.Add(-1);
		strings.Promote(hello_id);
		{
			LOG_DURATION("add in pop bottom");
			for (int i = 0; i < 1000000; i++) {
				strings.Add(i);
			}
		}
		{
			LOG_DURATION("is_valid");
			for (int i = 0; i < 1000000; i++) {
				strings.IsValid(hello_id);
			}
		}
		LOG_DURATION("pop bottom");
		strings.PopMax();
	}
	return 0;
}

