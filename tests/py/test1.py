import sys
import os
from itertools import combinations
import random
import string

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../python-service')))
from spell_corrector import edit_distance

import unittest


# python -m unittest discover


class Test(unittest.TestCase):

    def test_single_character_comparisons(self):
        characters = "abcdefghijklnopqrstuwxyz"
        polish_letters = "ąćęłńóśźż"
        all_chars = characters + polish_letters

        for c1, c2 in combinations(all_chars, 2):
            result = edit_distance(c1, c2)
            self.assertEqual(result, 1)

        for char in all_chars:
            result = edit_distance(char, char)
            self.assertEqual(result, 0)

    def test_same_words_randomly_generated(self):
        for _ in range(42):
            word_length = random.randint(1, 20)
            random_word = ''.join(random.choices(string.ascii_lowercase + string.digits, k=word_length))

            with self.subTest(word=random_word):
                self.assertEqual(edit_distance(random_word, random_word), 0,)


    def test_one_insertion_or_deletion(self):
        self.assertEqual(edit_distance("pies", "spies"), 1)
        self.assertEqual(edit_distance("spies", "pies"), 1)
        self.assertEqual(edit_distance("drzewo", "drzwo"), 1)

    def test_different_lengths(self):
        self.assertEqual(edit_distance("test", "testowanie"), 6)
        self.assertEqual(edit_distance("testowanie", "test"), 6)
        self.assertEqual(edit_distance("a", "b"), 1)
        self.assertEqual(edit_distance("abc", "d"), 3)

    def test_empty_strings(self):
        self.assertEqual(edit_distance("", "test"), 4)
        self.assertEqual(edit_distance("test", ""), 4)
        self.assertEqual(edit_distance("", ""), 0)


if __name__ == '__main__':
    unittest.main()
