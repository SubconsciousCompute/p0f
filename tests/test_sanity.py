__author__ = "Dilawar Singh"
__email__ = "dilawar@subcom.tech"

import p0f
print(f'[INFO] Loaded from {p0f.__file__}')

def test_sanity():
    print(dir(p0f))

if __name__ == '__main__':
    test_sanity()
