#!/usr/bin/env python3

def is_fizz(Num):
    """ If the input number is dividable by 3 or
        contains 3, then it is Fizz. """
    InputStr = str(Num)
    if (Num % 3 == 0) or ("3" in InputStr):
        return True
    else:
        return False


def is_buzz(Num):
    """ If the input number is dividable by 5 or
        contains 5, then it is Fizz. """
    InputStr = str(Num)
    if (Num % 5 == 0) or ("5" in InputStr):
        return True
    else:
        return False


def compute_fizz_buzz(MaxNum):
    results = []
    data = range(1, MaxNum+1)
    while data:
        flag = False
        tmp = []
        head = data[0]
        data = data[1:]
        if is_fizz(head):
            tmp.append("Fizz")
            flag = True
        if is_buzz(head):
            tmp.append("Buzz")
            flag = True
        if flag:
            results.append(" ".join(tmp).strip())
        else:
            results.append(str(head))
    return results


if __name__ == '__main__':
    MaxNum = 100
    V = 1
    for x in compute_fizz_buzz(MaxNum):
        print(V, " -> ", x)
        V += 1
