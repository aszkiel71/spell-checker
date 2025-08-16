import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../python-service')))
from spell_corrector import find_best_correction

import unittest

class Test(unittest.TestCase):

    def test_exact_match(self):
        res = find_best_correction("siema", ["siemaa", "k", "u", "lka", "siema"])
        self.assertEqual("siema", res)

    def test_empty_dictionary(self):
        res = find_best_correction("siema", [])
        self.assertEqual(None, res)

    def test_alphanumeric_input(self):
        res = find_best_correction("42", ["42", "34", "43"])
        self.assertEqual("42", res)

    def test_polish_characters_and_best_match(self):
        res = find_best_correction("polkownicaą", ["polkownica", "polkkkkk", "polkownicwąaą", "ąacinwolkop"])
        self.assertEqual("polkownica", res)

    def test_no_exact_match_but_best_is_close(self):
        res = find_best_correction("kompyter", ["komputer", "komputery", "kot", "pies"])
        self.assertEqual("komputer", res)

    def test_multiple_best_matches(self):
        res = find_best_correction("kot", ["kit", "kat", "pies"])
        self.assertIn(res, ["kit", "kat"])

    def test_different_cases(self):
        res = find_best_correction("Kot", ["kot", "pies", "lama"])
        self.assertEqual("kot", res)

if __name__ == '__main__':
    unittest.main()
