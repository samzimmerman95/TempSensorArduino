import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('temperat-fea82-firebase-adminsdk-gk4pn-3feb811dc0.secret.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://temperat-fea82.firebaseio.com/'
})

# As an admin, the app has access to read and write all data, regardless of Security Rules
ref = db.reference('test2')
all_data = ref.get()
print(len(all_data))
res = 0
for key, value in all_data.items():
    if int(value[1]) > 170:
        res += 1
        ref.child(key).set([value[0], value[0]])
print(res)
# print(ref.child('1684726299000').set({}))


# 1687999407000 first time plugged in after disaster. This is testing again