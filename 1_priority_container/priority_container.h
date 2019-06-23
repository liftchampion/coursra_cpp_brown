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

#ifndef PRIORITY_CONTAINER_H
#define PRIORITY_CONTAINER_H

#include <utility>
#include <vector>
#include <map>

using Id = unsigned long long int;

struct idx_prior{
	explicit idx_prior(Id new_idx) {
		prior = 0;
		idx = new_idx;
	}
	int	prior = 0;
	Id	idx = 0;
};

bool operator< (const idx_prior& lhs, const idx_prior& rhs) {
	if (lhs.prior < rhs.prior)
		return true;
	if (lhs.prior == rhs.prior)
		return lhs.idx < rhs.idx;
	return false;
}

template <typename T>
class PriorityCollection {
public:


	PriorityCollection() {
		make_heap(data.begin(), data.end());
		elements_count = 0;
	}
	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object) {
		Id id = elements_count++;
		data.push_back(idx_prior(id));
		push_heap(data.begin(), data.end());
		objs[id] = object; // fixme
		return id;
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
			 IdOutputIt ids_begin) {
		for (auto it = range_begin; it != range_end; ++it) {
			*ids_begin++ = Add(*range_begin);
		}
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const {
		return objs.find(id) != objs.end();
	}

	// Получить объект по идентификатору
	const T& Get(Id id) const {
		return objs[id];
	}

	// Увеличить приоритет объекта на 1
	void Promote(Id id) {
		//todo
	}

	// Получить объект с максимальным приоритетом и его приоритет
	std::pair<const T&, int> GetMax() const {
		//todo
	}

	// Аналогично GetMax, но удаляет элемент из контейнера
	std::pair<T, int> PopMax() {
		//todo
	}

private:
	std::vector<idx_prior> data;
	std::map<Id, T> objs;
	Id elements_count;
	// Приватные поля и методы
};

#endif //PRIORITY_CONTAINER_H
