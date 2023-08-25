import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('temperat-fea82-firebase-adminsdk-gk4pn-97d4eda3b1.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://temperat-fea82.firebaseio.com/'
})

# As an admin, the app has access to read and write all data, regardless of Security Rules
ref = db.reference('lake23')
lake23 = ref.get()
print(len(lake23))
res = 0
for key, value in lake23.items():
    if int(key) < 1684788739000:
        res += 1
        # ref.child(key).set({})
print(res)
# print(ref.child('1684726299000').set({}))


# 1687999407000 first time plugged in after disaster. This is testing again