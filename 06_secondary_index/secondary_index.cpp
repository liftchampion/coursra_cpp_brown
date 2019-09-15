#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <string_view>

using namespace std;

struct Record {
	string id;
	string title;
	string user;
	int timestamp;
	int karma;
};

// Реализуйте этот класс
class Database {
private:
	multimap<int, const Record&> time_to_id;
	multimap<int, const Record&> karma_to_id;
	multimap<string_view, const Record&> user_to_id;
	struct RecordData {
		explicit RecordData(const Record& rc) : rc(rc) {}
		Record rc;
		mutable decltype(time_to_id.begin()) time_it = {};
		mutable decltype(karma_to_id.begin()) karma_it = {};
		mutable decltype(user_to_id.begin()) user_it = {};
	};
	unordered_map<string, RecordData> id_to_data;
public:
	bool Put(const Record& record)
	{
		auto [iter, insertion_ok] = id_to_data.try_emplace(record.id, record);
		if (!insertion_ok) {
			return false;
		}

		const auto& record_data = iter->second;
		const auto& record_local = record_data.rc;
		record_data.time_it =
				time_to_id.emplace(record_local.timestamp, record_local);
		record_data.karma_it =
				karma_to_id.emplace(record_local.karma, record_local);
		record_data.user_it =
				user_to_id.emplace(record_local.user, record_local);
		return true;
	}
	const Record* GetById(const string& id) const {
		const auto it = id_to_data.find(id);
		return it == id_to_data.end() ? nullptr : &it->second.rc;

	}
	bool Erase(const string& id) {
		const auto it = id_to_data.find(id);
		if (it == id_to_data.end()) {
			return false;
		} else {
			const RecordData& rd = it->second;
			time_to_id.erase(rd.time_it);
			karma_to_id.erase(rd.karma_it);
			user_to_id.erase(rd.user_it);
			id_to_data.erase(it);
			return true;
		}
	}

	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const
	{
		auto begin = time_to_id.lower_bound(low);
		const auto end = time_to_id.end();
		while (begin != end && begin->first <= high &&
			callback(begin->second)) {
			++begin;
		}
	}

	template <typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const {
		auto begin = karma_to_id.lower_bound(low);
		const auto end = karma_to_id.end();
		while (begin != end && begin->first <= high &&
			   callback(begin->second)) {
			++begin;
		}
	}

	template <typename Callback>
	void AllByUser(const string& user, Callback callback) const {
		auto begin = user_to_id.find(user);
		const auto end = user_to_id.end();
		while (begin != end && begin->first == user &&
			   callback(begin->second)) {
			++begin;
		}
	}

private:

};

void TestRangeBoundaries() {
	const int good_karma = 1000;
	const int bad_karma = -10;

	Database db;
	db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
	db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

	int count = 0;
	db.RangeByKarma(bad_karma, good_karma, [&count](const Record& rc) {
		++count;
		cout << rc.user << endl;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestSameUser() {
	Database db;
	db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
	db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

	int count = 0;
	db.AllByUser("master", [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestReplacement() {
	const string final_body = "Feeling sad";

	Database db;
	db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
	db.Erase("id");
	db.Put({"id", final_body, "not-master", 1536107260, -10});

	auto record = db.GetById("id");
	ASSERT(record != nullptr);
	ASSERT_EQUAL(final_body, record->title);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestRangeBoundaries);
	RUN_TEST(tr, TestSameUser);
	RUN_TEST(tr, TestReplacement);
	return 0;
}