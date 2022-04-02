import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt 
import cv2
import math

model = tf.keras.models.load_model('number_guesser1.0')

imgs = []
data = []
ans = []

def loadimg(i, j):
    img = cv2.imread("otherData/" + str(i) + "." + str(j+1) + ".png", 0)
    new_array = cv2.resize(img, (28, 28))
    for a in range(28):
        for b in range(28):
            new_array[a][b] = abs(new_array[a][b] - 255)
    imgs.append(new_array)
    return new_array.reshape(-1, 28, 28, 1)

for i in range(10):
    for j in range(3):
        cur = loadimg(i, j)
        data.append(cur)
        p1 = model.predict([tf.keras.utils.normalize(cur)])
        p2 = model.predict([cur])
        if np.argmax(p1[0]) != np.argmax(p2[0]):
            print("XD?")
        ans.append(np.argmax(p2[0]))
succes_rate = 0
for i in range(30):
    correct = math.floor(i/3)
    ok = ""
    if(correct == ans[i]):
        ok = "tak"
        succes_rate += 1
    else:
        ok = "nie"
    
    print("poprawna odpowiedz:;", correct, ";odpowiedz algorytmu:;", ans[i], ";zgadza się?;", ok)

succes_rate /= 30
succes_rate *= 100

print("\npoprawnie odgadnieto ", succes_rate, "% przypadkow")
for i in range(30):
    plt.imshow(imgs[i], cmap = plt.cm.binary)
    plt.show()