from math import factorial


def _function(number1, number2):
    result = 0
    for i in range(number1):
        result += (pow(-1, i) * ((number1 - i) ** number2) * (
                factorial(number1) // (factorial(i) * factorial(number1 - i))))
    return result


def ratio(numerator, denominator, number):
    sign = 1
    if numerator < 0:
        numerator *= -1
        sign = -1
    if denominator == numerator:
        return sign, 1
    i = 2
    while True:
        if i > number:
            return numerator * sign, denominator
        if numerator % i == 0 and denominator % i == 0:
            numerator //= i
            denominator //= i
        else:
            i += 1


if __name__ == "__main__":
    value_map: [[int]] = []
    numerators: [int] = []
    denominators: [int] = []

    next_limit = int(input("Next Value Limit = "))

    numerators.append(0)
    denominators.append(1)

    for i in range(next_limit + 3):
        value_map.append([])
        for j in range(next_limit + 3):
            value_map[i].append(0)

    value_map[1][1] = int(input("Enter First Value = "))

    step = 1
    while True:
        numerators.append(0)
        denominators.append(1)

        for i in range(next_limit + (step - 1) * 2 + 3):
            value_map[i].append(0)
            value_map[i].append(0)
        value_map.append([])
        value_map.append([])
        for i in range(next_limit + step * 2 + 3):
            value_map[-1].append(0)
            value_map[-2].append(0)

        value_map[1][step + 1] = int(input("Enter Next  Value = "))

        for i in range(2, step + 2):
            for j in range(1, step + 3 - i):
                value_map[i][j] = value_map[i - 1][j + 1] - value_map[i - 1][j]
        i = 2
        while True:
            if i > step + 1 + next_limit:
                break
            for j in range(step + 1, 0, -1):
                value_map[j][i] = value_map[j + 1][i - 1] + value_map[j][i - 1]
                i += 1
            i -= step

        map_str = ""
        for i in range(1, step + next_limit + 2):
            for j in range(1, step + next_limit - i + 3):
                map_str += str(value_map[i][j]) + "\t"
            map_str += "\n"
        print(map_str)

        numerators[step] = value_map[step + 1][1]
        denominators[step] = factorial(step)
        numerators[0] = value_map[1][1]
        denominators[0] = 1

        for i in range(step - 1, 0, -1):
            denominators[i] = factorial(i) * denominators[i + 1]
            numerators[i] = value_map[i + 1][1] * denominators[i + 1]
            for j in range(1, step - i + 1):
                dx = step - j + 1
                numerators[i] -= ((denominators[i + 1] // denominators[dx]) * numerators[dx] * _function(i, dx))

        formula_str = ""
        for i in range(step, -1, -1):
            numerators[i], denominators[i] = ratio(numerators[i], denominators[i], step)
            if numerators[i] == 0:
                continue
            if numerators[i] >= 0 and len(formula_str) != 0:
                formula_str += "+"
            if numerators[i] != 1 and numerators[i] != -1 or i == 0:
                formula_str += str(numerators[i])
            elif numerators[i] == -1:
                formula_str += "-"
            if i >= 1:
                formula_str += "x"
            if i > 1:
                formula_str += "^" + str(i)
            if denominators[i] > 1:
                formula_str += "/" + str(denominators[i])
            formula_str += " "
        print(formula_str)
        step += 1
