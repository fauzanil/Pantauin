from firebase import firebase
import time
firebase = firebase.FirebaseApplication('https://pantauin.firebaseio.com/')

get = firebase.get('/users',None)


res = firebase.put('/users',"4","monty")

while 1:
    print (get)
    time.sleep(3)