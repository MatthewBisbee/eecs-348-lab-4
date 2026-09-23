"""Black-box checks using only Python's standard library."""
from pathlib import Path
import re
import subprocess
import unittest

ROOT = Path(__file__).resolve().parent.parent
COMBINATION = re.compile(r"(\d+) TD \+ 2pt, (\d+) TD \+ FG, (\d+) TD, (\d+) 3pt FG, (\d+) Safety")


def run(program, data):
    return subprocess.run([str(ROOT / program)], input=data, text=True,
                          capture_output=True, timeout=10)


class FootballTests(unittest.TestCase):
    def test_all_scores_through_100(self):
        # Independent coin-change DP counts unordered combinations.
        ways = [1] + [0] * 100
        for points in (2, 3, 6, 7, 8):
            for score in range(points, 101):
                ways[score] += ways[score - points]
        for score in range(101):
            if score == 1:
                continue
            with self.subTest(score=score):
                result = run('task1', f'{score}\n1\n')
                self.assertEqual(result.returncode, 0)
                rows = [tuple(map(int, m)) for m in COMBINATION.findall(result.stdout)]
                self.assertEqual(len(rows), ways[score])
                self.assertEqual(len(set(rows)), len(rows))
                self.assertEqual(rows, sorted(rows))
                for row in rows:
                    self.assertEqual(sum(n * p for n, p in zip(row, (8, 7, 6, 3, 2))), score)

    def test_pdf_sample(self):
        result = run('task1', '25\n1\n')
        actual = ['%s TD + 2pt, %s TD + FG, %s TD, %s 3pt FG, %s Safety' % row
                  for row in COMBINATION.findall(result.stdout)]
        expected = (ROOT / 'tests/score25_expected.txt').read_text().splitlines()
        self.assertEqual(actual, expected)

    def test_invalid_inputs_recover(self):
        invalid = ['-1', '-25', 'abc', '', '   ', '2.5', '2x', '2 3',
                   '2147483648', '9' * 100, '9' * 1000]
        for value in invalid:
            with self.subTest(value=value[:30]):
                result = run('task1', value + '\n2\n1\n')
                self.assertEqual(result.returncode, 0)
                self.assertIn('Invalid score:', result.stdout)
                self.assertEqual(COMBINATION.findall(result.stdout), [('0', '0', '0', '0', '1')])

    def test_repeat_stop_and_eof(self):
        self.assertEqual(len(COMBINATION.findall(run('task1', '0\n2\n3\n1\n25\n').stdout)), 3)
        self.assertNotIn('Possible combinations', run('task1', '1\n25\n').stdout)
        for data in ('', 'bad', '2', '  +2  \n1\n'):
            self.assertEqual(run('task1', data).returncode, 0)
        self.assertEqual(len(COMBINATION.findall(run('task1', '2').stdout)), 1)


class TemperatureTests(unittest.TestCase):
    def check_conversion(self, value, source, target, expected, category=None):
        result = run('task2', f'{value}\n{source}\n{target}\n')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn(f'Converted temperature: {expected:.2f} {target.upper()}', result.stdout)
        if category:
            self.assertIn(f'Temperature category: {category}\n', result.stdout)
        self.assertIn('Weather advisory:', result.stdout)
        return result.stdout

    def test_all_nine_scale_pairs(self):
        values = {'C': 30, 'F': 86, 'K': 303.15}
        for source, value in values.items():
            for target, expected in values.items():
                with self.subTest(source=source, target=target):
                    output = self.check_conversion(value, source, target, expected, 'Hot')
                    self.assertIn('Drink lots of water!', output)

    def test_category_boundaries_in_all_scales(self):
        for c, category in [(-0.01, 'Freezing'), (0, 'Cold'), (9.99, 'Cold'),
                            (10, 'Comfortable'), (24.99, 'Comfortable'),
                            (25, 'Hot'), (34.99, 'Hot'), (35, 'Extreme Heat')]:
            for source, value in [('C', c), ('F', c * 1.8 + 32), ('K', c + 273.15)]:
                for target in 'CFK':
                    expected = {'C': c, 'F': c * 1.8 + 32, 'K': c + 273.15}[target]
                    with self.subTest(c=c, source=source, target=target):
                        self.check_conversion(value, source, target, expected, category)

    def test_absolute_zero_and_negative_values(self):
        for source, value in [('C', -273.15), ('F', -459.67), ('K', 0)]:
            self.check_conversion(value, source, 'K', 0, 'Freezing')
        self.check_conversion(-40, 'C', 'F', -40, 'Freezing')
        self.check_conversion(-40, 'F', 'C', -40, 'Freezing')
        for source, value in [('C', -273.16), ('F', -459.68), ('K', -0.01)]:
            result = run('task2', f'{value}\n{source}\n30\nC\nF\n')
            self.assertIn('below absolute zero', result.stdout)
            self.assertIn('Converted temperature: 86.00 F', result.stdout)

    def test_invalid_temperature_recovery(self):
        for value in ['', ' ', 'abc', '30oops', '30 40', 'nan', 'inf', '-inf',
                      '1e999', '1e-999', '9' * 1000]:
            with self.subTest(value=value[:30]):
                result = run('task2', value + '\n30\nC\nF\n')
                self.assertIn('Invalid', result.stdout)
                self.assertIn('Converted temperature: 86.00 F', result.stdout)

    def test_scale_validation(self):
        for invalid in ['', ' ', 'X', 'Celsius', 'CF', '1', 'C' * 1000]:
            for data in [f'30\n{invalid}\nC\nF\n', f'30\nC\n{invalid}\nF\n']:
                result = run('task2', data)
                self.assertIn('Invalid', result.stdout)
                self.assertIn('Converted temperature: 86.00 F', result.stdout)
        self.check_conversion(' 3e1 ', ' c ', 'f', 86, 'Hot')

    def test_eof_and_extreme_values(self):
        for data in ['', '30\n', '30\nC\n', 'bad', '30\nC\nF']:
            self.assertEqual(run('task2', data).returncode, 0)
        result = run('task2', '1.7976931348623157e308\nC\nF\n')
        self.assertEqual(result.returncode, 1)
        self.assertIn('outside the supported numeric range', result.stderr)


if __name__ == '__main__':
    unittest.main(verbosity=2)
