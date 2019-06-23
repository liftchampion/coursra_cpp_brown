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

template <typename T>
class PriorityCollection {
public:
	using Id = int;

	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object) {
		//todo
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
			 IdOutputIt ids_begin) {
		//todo
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const {
		//todo
	}

	// Получить объект по идентификатору
	const T& Get(Id id) const {
		//todo
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
	// Приватные поля и методы
};

#endif //PRIORITY_CONTAINER_H
