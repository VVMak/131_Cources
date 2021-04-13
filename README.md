# Задача 131

## Описание алгоритма

Класс Solver для каждой вершины дерева курсов находит все наборы курсов более низкого уровня, которые нужно пройти, чтобы приступить к данному.
Для решения этой задачи используем динамику по дереву, начиная подсчет с курсов более низкого уровня. 

Поиск вариантов для данной вершины: рекурсивно перебираем все зависимости и для каждой зависимости все её варианты.

Таким образом, предпосчитав динамику, мы сможем для каждого ученика с индивидуальным набором выбранных курсов (3 курса третьего уровня и 1 пятого) находить курсы, которые ему точно придется пройти.


## TODO

Мы знаем набор курсов, которые точно придется пройти. Нужно выполнить проверку на то, что в каждом семестре получится проходить сколько-то курсов из выбранного набора. Для этого возьмем индуцированный граф и жадным алгоритмом будем каждый семестр пытаться пройти листья (когда прошли, условно убираем курсы из дерева). Если в какой-то момент окажется, что мы не можем пройти требуемое кол-во курсов, то нужно дополнять исходный набор.
