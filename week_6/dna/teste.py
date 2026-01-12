def checkRepetitions(string, substring):
    totalLen = len(string)
    subLen = len(substring)
    count = 0
    repList = []
    for i in range(totalLen):
        if string[i:i + subLen] == substring:
            for j in range(i, totalLen, subLen):
                if string[j:j + subLen] == substring:
                    count += 1
                else:
                    repList.append(count)
                    count = 0

    return max(repList)

