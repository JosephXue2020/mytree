import time

import tqdm

from ztflforest import forest


if __name__ == '__main__':
    try:
        tr = forest.get('original')
    except Exception as e:
        print(e)

    num = 1000
    code = 'TP319'
    start = time.time()
    for i in tqdm.tqdm(range(num)):
        node = tr.search(code)
        # print(node.identifier())
    end = time.time()
    print('耗时：', end-start)