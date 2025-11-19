import csv
import sys


def checkReps(string, substring):
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

    if repList == []:
        return 0
    else:
        return max(repList)


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Error, Type again.")

    # TODO: Read database file into a variable

    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        fnames = reader.fieldnames
        del fnames[0]

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2], "r") as txtfile:
        reader2 = txtfile.read()

    # TODO: Find longest match of each STR in DNA sequence

    # print(checkReps(reader2, fnames[0]))

    checklist = []
    for i in range(len(fnames)):
        checklist.append(checkReps(reader2, fnames[i]))

    # TODO: Check database for matching profiles
    name = 'Error'
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            allvalues = list(row.values())
            for i in range(1, len(allvalues)):
                allvalues[i] = int(allvalues[i])
            if allvalues[1:] == checklist:
                name = allvalues[0]

    if name != 'Error':
        print(name)
    else:
        print("No Match.")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
