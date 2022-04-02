import matplotlib.pyplot as plt 
import tensorflow as tf

mnist = tf.keras.datasets.mnist

(x_train, y_train), (x_test, y_test) = mnist.load_data() #28.28 px 256 color pics
x_train = tf.keras.utils.normalize(x_train, axis = 1)
x_test = tf.keras.utils.normalize(x_train, axis = 1)
#plt.imshow(x_train[0], cmap = plt.cm.binary)
#plt.show()

model = tf.keras.models.Sequential()

model.add(tf.keras.layers.Flatten())

model.add(tf.keras.layers.Dense(128, activation = tf.nn.relu))
model.add(tf.keras.layers.Dense(128, activation = tf.nn.relu))

model.add(tf.keras.layers.Dense(10, activation = tf.nn.softmax))

model.compile(optimizer ='adam', 
                loss='sparse_categorical_crossentropy', 
                metrics=['accuracy'])


model.fit(x_train, y_train, epochs = 3)


model.save('number_guesser1.0')

#loss: 0.0708 - accuracy: 0.9778