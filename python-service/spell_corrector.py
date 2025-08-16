import sys

def edit_distance(s, t):
    m = len(s)
    n = len(t)
    d = [[0 for _ in range(n + 1)] for _ in range(m + 1)]


    for i in range(m + 1):
        d[i][0] = i
    for j in range(n + 1):
        d[0][j] = j


    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s[i-1] == t[j-1]:
                cost = 0
            else:
                cost = 1
            d[i][j] = min(
                d[i-1][j] + 1,
                d[i][j-1] + 1,
                d[i-1][j-1] + cost
            )

    return d[m][n]



def find_best_correction(wrong_word, dictionary_words):
    candidates = [(word, edit_distance(word, wrong_word))
                 for word in dictionary_words
                 if edit_distance(word, wrong_word) <= 3]
                            # you can modify radius

    if not candidates:
        return None


    best_word = min(candidates, key=lambda x: x[1])
    return best_word[0]


if __name__ == "__main__":
    if(len(sys.argv) < 3):
        raise NotImplementedError
    wrong_word = sys.argv[1]
    dictionary_string = sys.argv[2]
    dict = dictionary_string.split(",")
    result = find_best_correction(wrong_word, dict)
    print(result)
