from ztfl.ztflforest import forest
import time
import tqdm


# 测试时挪到ztcata-lab2/pkg目录下

if __name__ == '__main__':
    tr = forest.get('original')

    num = 1000
    code = 'TP319'
    start = time.time()
    for i in tqdm.tqdm(range(num)):
        node = tr.get(code)
    end = time.time()
    print('耗时：', end-start)