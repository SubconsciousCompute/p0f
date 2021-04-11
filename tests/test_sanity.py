__author__ = "Dilawar Singh"
__email__ = "dilawar@subcom.tech"

import p0f
print(f'[INFO] Loaded from {p0f.__file__}')

def test_sanity():
    v = p0f.__version__
    #  interfaces = p0f.list_interfaces()
    #  print(interfaces)

    print(f'version {p0f.__version__}')
    assert v[0] == '3', v
    p0f.start('/tmp/p0f.socket')


    p0f.stop()

if __name__ == '__main__':
    test_sanity()
